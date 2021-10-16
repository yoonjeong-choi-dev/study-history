#include <unistd.h>
#include <stdio.h>

// 무한 루프를 이용하여 부모, 자식 프로세스에서 정보 출력
#define FOREVER \
    ;           \
    ;

// 부모 프로세스에서 실행시킬 함수
void parent_function()
{
    int parent_count = 0;

    for (FOREVER)
    {
        printf("Parent Process - count: %d\n", parent_count);
        parent_count++;
        // 3초간 정지
        sleep(3);
    }
}

// 자식 프로세스에서 실행시킬 함수
void child_function()
{
    int child_count = 0;

    for (FOREVER)
    {
        printf("Child Process - count: %d\n", child_count);
        child_count++;

        // 5초간 정지
        sleep(5);
    }
}

int main()
{
    int child_pid;
    child_pid = fork();

    // 0인 경우 : 자식 프로세스
    if (child_pid == 0)
    {
        printf("<< 자식 프로세스 생성 >>\n");
        child_function();
    }
    // 0보다 큰 경우 : 부모 프로세스에 해당
    else if (child_pid > 0)
    {
        printf("<< 부모 -자식 프로세스 번호 : %d >>\n", child_pid);
        parent_function();
    }
    // 0보다 작은 경우 : 프로세스 생성 실패
    else
    {
        printf("프로세스 생성에 실패\n");
    }

    return 0;
}