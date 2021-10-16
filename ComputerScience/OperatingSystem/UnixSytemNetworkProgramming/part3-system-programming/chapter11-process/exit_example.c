#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int step = 0;

    int child_pid;
    child_pid = fork();

    // 자식 프로세스
    if (child_pid == 0)
    {
        printf("<< 자식 프로세스 >>\n");
        for (step = 0; step < 2; step++)
        {
            printf("자식 실행 횟수 : %d\n", step);
            sleep(1);
        }

        exit(1);
    }
    // 부모 프로세스
    else if (child_pid > 0)
    {
        printf("<< 부모 프로세스 >>\n");
        for (step = 0; step < 3; step++)
        {
            printf("부모 실행 횟수 : %d\n", step);
            sleep(1);
        }
        exit(1);
    }
    else
    {
        printf("프로세스 생성 실패");
    }

    return 0;
}