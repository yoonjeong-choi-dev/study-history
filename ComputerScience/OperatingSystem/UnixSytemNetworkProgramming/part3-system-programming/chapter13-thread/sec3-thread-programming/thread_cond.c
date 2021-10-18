#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// 2개의 스레드에서 사용할 뮤텍스
pthread_mutex_t thread1_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t thread2_mutex = PTHREAD_MUTEX_INITIALIZER;

// 시그널을 전송 받을 스레드 조건 변수 : 2개 이상의 스레드 사이의 잠금 상태 확인용
pthread_cond_t checker = PTHREAD_COND_INITIALIZER;

// 스레드에서 접근하는 전역 변수 및 함수 
int count_number = 0;

void set_count()
{
    count_number++;
    sleep(1);
}


// 스레드 1 메인 함수
void* thread1_main()
{
    printf("Thread 1 is RUNNING\n");

    while(1)
    {
        // 메인 함수 종료 조건
        if(count_number > 5) pthread_exit(0);

        // 뮤텍스을 잠금 실행
        pthread_mutex_lock(&thread1_mutex);

        // 전역 변수 접근
        set_count();
        printf("Thread 1 : %d\n", count_number);

        // 시그널을 다른 스레드에 전송
        pthread_cond_signal(&checker);

        // 다른 스레드의 시그널을 기다린다 : 스레드 2의 시그널 대기
        pthread_cond_wait(&checker, &thread1_mutex);

        // 뮤텍스 잠금 해제
        pthread_mutex_unlock(&thread1_mutex);
    }
}

// 스레드 2 메인 함수
void* thread2_main()
{
    printf("Thread 2 is RUNNING\n");

    while(1)
    {
        // 메인 함수 종료 조건
        if(count_number > 5) pthread_exit(0);

        // 뮤텍스을 잠금 실행
        pthread_mutex_lock(&thread2_mutex);

        // 다른 스레드의 시그널을 기다린다 : 스레드 1의 시그널 대기
        pthread_cond_wait(&checker, &thread2_mutex);

        // 전역 변수 접근
        set_count();
        printf("Thread 2 : %d\n", count_number);

        
        // 시그널을 다른 스레드에 전송
        pthread_cond_signal(&checker);

        // 뮤텍스 잠금 해제
        pthread_mutex_unlock(&thread2_mutex);
    }
}

int main()
{   
    int ret;
    pthread_t thread1, thread2;
    
    // 스레드 1 생성
    ret = pthread_create(&thread1, NULL, thread1_main, NULL);
    if(ret != 0)
    {
        printf("Fail to create Thread 1\n");
        return 0;
    }

    // 스레드 2 생성
    ret = pthread_create(&thread2, NULL, thread2_main, NULL);
    if(ret != 0)
    {
        printf("Fail to create Thread 2\n");
        return 0;
    }

    // 모든 스레드 작업이 종료할 때까지 대기
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // 뮤텍스 및 조건 변수 제거
    pthread_mutex_destroy(&thread1_mutex);
    pthread_mutex_destroy(&thread2_mutex);
    pthread_cond_destroy(&checker);

    return 1;
}