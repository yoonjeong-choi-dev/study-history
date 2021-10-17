#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// subthread function
void* sub_thread_main(void* arg)
{
    while(1)
    {
        sleep(2);
        printf("Sub Thread is running!\n");
    }
}


int main()
{
    // 쓰레드 구조체 선언
    pthread_t sub_thread;

    // 쓰레드 생성
    int ret;
    ret = pthread_create(&sub_thread, NULL, sub_thread_main, NULL);
    if(ret != 0)
    {
        printf("Fail to create a sub thread\n");
        return 0;
    }

    // main thread
    while(1)
    {
        sleep(1);
        printf("Main Thread is running!\n");
    }

    return 1;
}