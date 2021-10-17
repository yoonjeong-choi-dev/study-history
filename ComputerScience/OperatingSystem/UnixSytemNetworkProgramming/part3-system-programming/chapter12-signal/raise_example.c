#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SIGTERM handler
int stop_handler()
{
    printf("\n\nstop handler is called\n");
    sleep(1);
    printf("\n<< 작업 종료 진행 >>\n");
    sleep(1);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("\n\nusage : %s <seconds>", argv[0]);
        exit(1);
    }

    int second, step = 1;
    second = atoi(argv[1]);

    // hander setting
    signal(SIGTERM, stop_handler);

    while(step<=second)
    {
        sleep(1);
        printf("%d task is done\n", step);
        step++;
    }

    // 시그널 발생 => 종료
    raise(SIGTERM);

    return 1;
}