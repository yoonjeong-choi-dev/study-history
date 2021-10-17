#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// SIGTERM handler
int sigterm_handler()
{
    printf("\n\nSIGTERM hander is called\n");
    sleep(1);
    printf("\n<< 작업 종료 진행 >>\n");
    exit(1);
}

int main()
{
    int result, step = 0;

    printf("SIGTERM handler setting\n\n");
    result = signal(SIGTERM, sigterm_handler);

    printf("\n<<< Main Process is running, PID: %d >>>\n", getpid());
    while(1)
    {
        step++;
        printf("%d task is done\n", step);
        sleep(1);
    }

    return 1;
}