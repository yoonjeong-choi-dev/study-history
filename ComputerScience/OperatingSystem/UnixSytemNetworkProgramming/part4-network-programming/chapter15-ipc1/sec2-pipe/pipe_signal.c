#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32

// SIGPIPE 시그널을 처리하는 핸들러
// SIGPIPE : read를 수행하는 프로세스가 종료하여, write을 할 때 문제가 생기는 경우
void sigpipe_handler(int signum)
{
    // 필요한 작업을 처리 후, 프로그램 종료
    printf("\n파이프가 비정상적으로 닫혔습니다\n");
    printf("SIGPIPE handler is called, Task is to be end...\n");
    sleep(1);
    printf("\n<< TASK END >>\n");
    exit(1);
}

int main()
{
    // 입출력 버퍼 및 파일 기술어 정의
    char putMsg[BUFFER_SIZE], getMsg[BUFFER_SIZE];
    int pipeDescriptors[2];

    // 자식 프로세스 용 PID
    int child_pid = 0;

    // 시그널 핸들러 등록
    printf("SIGPIPE hander setting\n\n");
    signal(SIGPIPE, sigpipe_handler);

    // 파이프 생성
    if (pipe(pipeDescriptors) == -1)
    {
        printf("Fail to create a pipe\n");
        return 0;
    }

    // 자식 프로세스 생성
    child_pid = fork();

    // 자식 프로세스에서는 입력 파이프(파이프 읽기) 사용
    if (child_pid == 0)
    {
        printf("\n<< Child Proccess is RUNNING >>\n");
        while (1)
        {
            read(pipeDescriptors[0], getMsg, BUFFER_SIZE);
            printf("Child gets message : %s\n", getMsg);

            if (!strncmp(getMsg, "quit", 4))
            {
                printf("\n<< Child Proccess is STOPPED >>\n");
                exit(1);
            }
        }
    }
    // 부모 프로세스에서는 사용자 입력을 받아 출력 파이프(파이프 쓰기) 사용
    else if (child_pid > 0)
    {
        printf("\n<< Parent Proccess is RUNNING >>\n");
        sleep(1);
        while (1)
        {
            // 파이프에 넣을 메시지를 사용자에게 입력 받음
            printf("Parent input message : ");
            gets(putMsg);

            // quit 입력 시
            if(!strncmp(putMsg, "quit", 4))
            {
                // 입력 파이프 닫기
                close(pipeDescriptors[0]);
                write(pipeDescriptors[1], putMsg, BUFFER_SIZE);
                sleep(1);
            }

            // 해당 메시지를 파이프에 쓰기
            // QUIT의 경우, 자식 프로세스는 두번 read하면서 SIGPIPE 시그널 발생
            write(pipeDescriptors[1], putMsg, BUFFER_SIZE);
            sleep(1);

            
            
        }
    }
    else
    {
        printf("Fail to create a process\n");
    }

    return 1;
}