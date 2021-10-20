#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32

int main()
{
    // 입출력 버퍼 및 파일 기술어 정의
    char putMsg[BUFFER_SIZE], getMsg[BUFFER_SIZE];
    int pipeDescriptors[2];

    // 자식 프로세스 용 PID
    int child_pid = 0;

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

            // 해당 메시지를 파이프에 쓰기
            write(pipeDescriptors[1], putMsg, BUFFER_SIZE);

            if (!strncmp(putMsg, "quit", 4))
            {
                exit(1);
            }

            sleep(1);
        }
    }
    else
    {
        printf("Fail to create a process\n");
    }

    return 1;
}