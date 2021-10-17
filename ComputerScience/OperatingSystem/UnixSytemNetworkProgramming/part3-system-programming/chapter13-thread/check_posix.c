#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    printf("POSIX version : %ld\n", _POSIX_VERSION);

    if(_POSIX_VERSION < 199500L)
    {
        printf("시스템이 POSIX1003.1c 스레드를 지원하지 않음\n");
    }
    else
    {
        printf("시스템이 POSIX1003.1c 스레드를 지원\n");
    }

#ifdef _POSIX_THREAD_PRIORITY_SCHEDULING
    printf("우선 순위 스케줄링 지원\n");
#else
    printf("우선 순위 스케줄링 지원하지 않음\n");
#endif

    return 1;
}