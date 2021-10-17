#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// SIGINT 시그널 핸들러
int sigint_handler()
{
    printf("\n\n SIGINT 핸들러 호출\n\n");
    printf("\n<< 작업 종료 시작 >>\n");
    sleep(1);
    printf("\n\nStop the process\n\n");
    printf("All open files are closed\n\n");
    printf("\n<< 작업 종료 >>\n");
    exit(1);
}


int main()
{
    int result, step = 0;

    printf("SIGINT handler Setting \n\n");
    result = signal(SIGINT, sigint_handler);

    printf("\n<< Main Process is running >>\n");
    printf("Some files are opened\n");
    while(1)
    {
        step++;
        printf("%d 번째 작업 수행\n", step);
        sleep(1);
    }

    return 1;
}