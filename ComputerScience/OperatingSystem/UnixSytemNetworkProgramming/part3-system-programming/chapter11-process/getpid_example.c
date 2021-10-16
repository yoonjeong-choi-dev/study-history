#include <unistd.h>
#include <stdio.h>

int main()
{
    int child_pid, parent_pid;

    // 자기 자신의 PID
    parent_pid = getpid();

    // 자식 프로세스 생성
    child_pid = fork();

    // 자식 프로세스인 경우
    if (getpid() != parent_pid)
    {
        printf("<< Child Process >>\n");
        printf("PID: %d, Parent PID: %d\n", getpid(), getppid());
    }
    // 부모 프로세스인 경우
    else if (getpid() == parent_pid)
    {
        printf("<< Parent Process >>\n");
        printf("PID: %d, Parent PID: %d\n", getpid(), getppid());
    }
    else
    {
        printf("Fail to create a process\n");
    }

    return 0;
}