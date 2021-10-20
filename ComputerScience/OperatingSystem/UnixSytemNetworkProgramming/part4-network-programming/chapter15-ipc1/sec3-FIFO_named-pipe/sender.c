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

// 메시지 송신 프로세스
int main()
{
    // 파일 기술자 및 버퍼 선언
    int file_descriptor;
    char buffer[MESSAGE_SIZE];

    // FIFO 열기
    file_descriptor = open(PIPE_NAME, O_WRONLY);
    if (file_descriptor < 0)
    {
        printf("Fail to open FIFO pipe\n");
        return 0;
    }

    // 메시지를 계속 전송한다
    while(1)
    {
        // 사용자에게서 전송할 메시지를 입력 받는다
        printf("메시지 입력 : ");
        gets(buffer);

        // 입력받은 메시지를 파이프에 작성
        if(write(file_descriptor, buffer, MESSAGE_SIZE) == -1)
        {
            printf("Fail to write message\n");
            break;
        }
        else
        {
            // quit이면 종료
            if(!strncmp(buffer, "quit", 4))
            {
                exit(0);
            }
        }
    }

    return 1;
}