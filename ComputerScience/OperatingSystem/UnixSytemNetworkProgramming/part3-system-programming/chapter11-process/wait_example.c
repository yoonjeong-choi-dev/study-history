#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>


int main()
{
    int count, child_pid;
    child_pid = fork();

    if (child_pid == 0)
    {
        printf("<< 자식 프로세스 생성 >>\n");

        for (count = 0; count < 2; count++)
        {
            printf("Child process - count : %d\n", count);
            sleep(1);
        }
    }
    else if (child_pid > 0)
    {
        // 자식 프로세스가 끝날 때까지 대기
        wait((int*)0);

        printf("<< 부모-자식 프로세스 번호 : %d >>\n", child_pid);
        for (count = 0; count < 2; count++)
        {
            printf("Parent process - count : %d\n", count);
            sleep(1);
        }
    }
    else
    {
        printf("프로세스 생성 실패\n");
    }

    return 0;
}