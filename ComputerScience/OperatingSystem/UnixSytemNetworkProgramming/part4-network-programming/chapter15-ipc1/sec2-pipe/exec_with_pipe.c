#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // 파일 기술어 정의
    int pipeDescriptors[2];

    // 자식 프로세스 용 PID
    int child_pid = 0;

    // 실행할 2개의 명령어 정의
    char* ps[3] = {"ps", "-ef", NULL};
    char* grep[3] = {"grep", "sys", NULL};

    // 파이프 생성
    if (pipe(pipeDescriptors) == -1)
    {
        printf("Fail to create a pipe\n");
        return 0;
    }


    // 자식 프로세스 생성 : 첫번째 명령어 실행 용
    child_pid = fork();

    // 자식 프로세스 : 첫번쨰 명령어 ps 실행 후 다음 명령어로 결과 전달
    if (child_pid == 0)
    {
        printf("\n<< Child Proccess is RUNNING : ps -ef >>\n");
        
        // 결과를 저장하는 출력 파이프(파이프 쓰기)의 파일 기술어 대체
        // 해당 명령어의 결과 값을 다음 명령어에게 전달하기 위해 output을 write
        dup2(pipeDescriptors[1], 1);    // 두번째 인자 1은 표준 출력 의미

        // 기존 파이프는 닫아 준다
        close(pipeDescriptors[0]);
        close(pipeDescriptors[1]);

        // 명령어 실행
        execvp(ps[0], ps);

        // 이후 명령어가 실행되지 않음
        printf("ps 실행 실패!\n");
    }
    // 부모 프로세스 : 두번째 명렁어 grep 실행. 이전 명령어 결과를 받아온다
    else if (child_pid > 0)
    {
        printf("\n<< Parent Proccess is RUNNING : grep sys >>\n");

        // 이전 결과를 읽어오는 입력 파이프(파이프 읽기)의 파일 기술어 대체
        // 해당 명령어 실행의 input을 read
        dup2(pipeDescriptors[0], 0);    // 두번째 인자 0은 표준 입력 의미

        // 기존 파이프는 닫아 준다
        close(pipeDescriptors[0]);
        close(pipeDescriptors[1]);

        // 명령어 실행
        execvp(grep[0], grep);

        // 이후 명령어가 실행되지 않음
        printf("grep 실행 실패!\n");
    }
    else
    {
        printf("Fail to create a process\n");
    } 

    return 0;
}