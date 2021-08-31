#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#define BUFFER_SIZE (100 * 1024 * 1024)
#define NCYCLE 10
#define PAGE_SIZE 4096

int main(void)
{

    char *p;
    time_t t;
    char *s;

    // 메모리 획득 전 시간 측정
    t = time(NULL);
    s = ctime(&t);

    // 메모리 획득 전 : 엔터키 입력 대기
    printf("%.*s: before allocation, please Enter key\n", (int)(strlen(s) - 1), s);
    getchar();

    // 메모리 획득 : 가상 메모리 확보
    p = malloc(BUFFER_SIZE);
    if (p == NULL)
        err(EXIT_FAILURE, "malloc() failed");

    // 메모리 획득 후 시간 측정
    t = time(NULL);
    s = ctime(&t);

    printf("%.*s: allocated %dMB, please Enter key\n", (int)(strlen(s) - 1), s, BUFFER_SIZE / (1024 * 1024));
    getchar();

    // 실제 접근을 통한 물리 메모리 확보
    int i;
    for (i = 0; i < BUFFER_SIZE; i += PAGE_SIZE)
    {
        p[i] = 0;
        int cycle = i / (BUFFER_SIZE / NCYCLE);
        
        // 10MB 접근이 끝날때마다 진행상황 출력
        if (cycle != 0 && i % (BUFFER_SIZE / NCYCLE) == 0)
        {
            t = time(NULL);
            s = ctime(&t);

            printf("%.*s: touched %dMB\n", (int)(strlen(s) - 1), s, i / (1024 * 1024));
            sleep(1);
        }
    }

    t = time(NULL);
    s = ctime(&t);

    printf("%.*s: touched %dMB, please Enter key\n", (int)(strlen(s) - 1), s, BUFFER_SIZE / (1024 * 1024));
    getchar();

    exit(EXIT_SUCCESS);
}