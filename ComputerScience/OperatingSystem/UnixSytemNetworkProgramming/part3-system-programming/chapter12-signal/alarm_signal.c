#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


int user_input;

// SIGALRM Handler
int alarm_handler()
{
    printf("\nTime is UP!\n");
    user_input = -1;
    return 1;
}

int main()
{
    signal(SIGALRM, alarm_handler);
    
    // 알람 세팅 : 3초
    alarm(3);

    // 3초 내로 입력 받기
    printf("3초 내로 입력하세요 : ");
    scanf("%d", &user_input);

    // 알람 타이머 해제
    alarm(0);


    printf("Your input : %d\n", user_input);

    return 1;
}