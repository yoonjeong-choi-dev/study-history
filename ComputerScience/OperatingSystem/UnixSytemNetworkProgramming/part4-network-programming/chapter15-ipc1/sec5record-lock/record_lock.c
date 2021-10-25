#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    // 파일을 위한 변수
    int file, step;

    for(step = 0; step < 5; step++)
    {
        // 파일 열기
        file = open("./data.txt", O_CREAT|O_WRONLY|O_APPEND);
        if (file < 0)
        {
            fprintf(stderr, "Fail to open file\n");
            exit(0);
        }

        // 파일 전체에 대한 lock 수행 및 파일 쓰기
        printf("Lock file ... - %d\n", step);
        lockf(file, F_LOCK, 0L);
        write(file, "Record Lock Message\n", 20);

        // 파일 전체에 대한 unlock 수행 및 파일 닫기
        printf("Unlock file ... - %d\n", step);
        lockf(file, F_ULOCK, 0L);
        close(file);

        sleep(1);
    }

    exit(1);
}