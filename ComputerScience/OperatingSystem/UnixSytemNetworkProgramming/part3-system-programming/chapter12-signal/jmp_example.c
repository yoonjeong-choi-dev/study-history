#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 점프할 위치를 저장하는 변수
jmp_buf jmp_pos;
int jmp_count;

void run_jump(int signum)
{
    // 점프 카운트 저장
    printf("<< SIGINT Occurs! >>\n");
    jmp_count++;
    if(jmp_count < 3)
    {
        printf("아직 종료할 수 없습니다\n");
    }
    else
    {
        printf("\n종료 모듈로 갑니다\n");
    }

    // setjmp에 jmp_count 인자 넘겨준다
    //signal(SIGINT, SIG_IGN);
    longjmp(jmp_pos, jmp_count);
}   

int main()
{   
    // 카운터 초기화
    jmp_count = 0;

    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = &run_jump;
    sa.sa_flags = 0 ;

    int ret;
    
    // 시스템 종료 모듈 라인 
    ret = setjmp(jmp_pos);
    printf("jmp result : %d\n", ret);
    if(ret >= 3)
    {
        printf("\n시스템 종료 중...\n");
        sleep(2);
        exit(1);
    }

    // handler setting
    printf("\nSIGINT handler is set\n");
    // 
    // sigemptyset(&(sa.sa_mask));
    // sigaddset(&(sa.sa_mask), SIGINT);
    sigaction(SIGINT, &sa, NULL);


    //signal(SIGINT, run_jump);
    while(1)
    {
        sleep(1);
        printf("%d 번째 단계로 프로그램 실행 중\n", ret);
    }

    return 1;
}