#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filename> \n\n", argv[0]);
        return -1;
    }

    // 파일을 생성하고 쓰기 위한 FILE 포인터와 버퍼
    FILE *pfile;
    char buffer[BUFFER_SIZE];
    char *gets_ret;
    int buffer_len;

    // 파일 생성
    pfile = fopen(argv[1], "w");
    if (pfile == 0)
    {
        printf("%s file open failed\n", argv[1]);
        return -1;
    }

    while (1)
    {
        // 표준 입력을 통해 받아온 데이터를 버퍼에 저장
        printf("Input data('quit' to stop) : ");
        gets_ret = gets(buffer);
        if (gets_ret == NULL)
        {
            printf("Buffer size(255) is over. Please enter a shorter sentence\n");
        }

        buffer_len = strlen(buffer);

        if (buffer_len == 4 && !strncmp(buffer, "quit", 4))
        {
            break;
        }
        // 개행 문자 추가 공간이 있는 경우에만, 파일에 write
        else if (buffer_len < 255)
        {
            // 개행 문자 추가 후, 생성된 파일에 write
            sprintf(buffer, "%s\n", buffer);
            fputs(buffer, pfile);
        }
        else
        {
            printf("Buffer size(255) is over. Please enter a shorter sentence\n");
        }
    }

    // 리소스 정리
    fclose(pfile);
    return 0;
}