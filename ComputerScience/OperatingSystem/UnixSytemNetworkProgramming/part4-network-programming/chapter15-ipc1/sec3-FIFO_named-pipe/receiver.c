#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

// 메시지 사이즈 정의
#define MESSAGE_SIZE 64

// 통신 파이프 이름 정의
#define PIPE_NAME "FIFO"

// 메시지 수신 프로세스
int main()
{
    // 파일 기술자 및 버퍼 선언
    int file_descriptor;
    char buffer[MESSAGE_SIZE];

    // FIFO(네임드 파이프) 생성
    if (mkfifo(PIPE_NAME, 0666) == -1)
    {
        if (errno != EEXIST)
            printf("Fail to create FIFO\n");
    }

    // FIFO 열기
    file_descriptor = open(PIPE_NAME, O_RDWR);
    if (file_descriptor < 0)
    {
        printf("Fail to open FIFO pipe\n");
        return 0;
    }

    // 메시지를 파이프에서 계속 읽어 온다
    while (1)
    {
        if(read(file_descriptor, buffer, MESSAGE_SIZE) < 0)
        {
            printf("Fail to read message\n");
            break;
        }
        else
        {
            printf("Message to read : %s\n", buffer);

            // quit이면 종료
            if(!strncmp(buffer, "quit", 4))
            {
                exit(0);
            }
        }
    }

    return 1;
}