#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// 자식 프로세스에서 실행 시키는 함수
void child_function()
{
    printf("<< 자식 프로세스 대체 >>");

    // exec을 이용하여 자식 프로세스를 부모와 전혀 상관없는 프로세스로 대체
    execl("/usr/bin/ls", "ls", "-alF", (char *)0);

    // 실패시 에러 표시
    printf("exec() 실행에 에러 발생\n");
    exit(-1);
}

int main()
{
    int parent_count = 0;

    int child_pid;
    child_pid = fork();

    if (child_pid == 0)
    {
        printf("<< 자식 프로세스 생성 >>\n");
        child_function();
    }
    else if (child_pid > 0)
    {
        printf("<< 부모-자식 프로세스 번호 : %d >>\n", child_pid);
        for (parent_count = 0; parent_count < 2; parent_count++)
        {
            printf("Parent Process - count: %d\n", parent_count);
            sleep(1);
        }
    }
    else
    {
        printf("프로세스 생성 실패\n");
    }

    return 0;
}