#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>

pthread_attr_t sub_thread_attr;

// subthread function
void* sub_thread_main(void* arg)
{
    size_t memory_size;

    // 스레드의 스택 메모리 사이즈 출력
    pthread_attr_getstacksize(&sub_thread_attr, &memory_size);
    printf("서브 스레드 attr의 스택 사이즈 : %ld\n", memory_size);
    pthread_exit(0);
}


int main()
{
    printf("PTHREAD_STACK_MIN(스레드 스택 최소 사이즈) : %d\n", PTHREAD_STACK_MIN);
    // 쓰레드 구조체 선언
    pthread_t sub_thread;
    size_t memory_size;

    // 스레드 속성 설정
    pthread_attr_init(&sub_thread_attr);
    
    pthread_attr_getstacksize(&sub_thread_attr, &memory_size);
    printf("스레드 attr의 초기 스택 사이즈 : %ld\n", memory_size);

    pthread_attr_setstacksize(&sub_thread_attr, 1024*20);
    pthread_attr_getstacksize(&sub_thread_attr, &memory_size);
    printf("메인 스레드 attr의 스택 사이즈 : %ld\n", memory_size);

    // 쓰레드 생성
    int ret;
    ret = pthread_create(&sub_thread, &sub_thread_attr, sub_thread_main, NULL);
    if(ret != 0)
    {
        printf("Fail to create a sub thread\n");
        return 0;
    }

    pthread_join(sub_thread, NULL);

    // 스레드 속성 제거
    pthread_attr_destroy(&sub_thread_attr);

    return 1;
}