#include <stdio.h>
#include <unistd.h>

// 오직 하나만 돌아야 하는 프로세스 예제
int main()
{
    while(1)
    {
        fprintf(stdout, "ONLY ONE PROCESS RUNNING\n");
        sleep(1);
    }
}