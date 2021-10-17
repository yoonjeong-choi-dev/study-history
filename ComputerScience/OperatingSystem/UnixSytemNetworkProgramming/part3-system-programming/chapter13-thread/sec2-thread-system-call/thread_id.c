#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// subthread function
void* sub_thread_main(void* arg)
{
    pthread_t sub_thread_id = pthread_self();
    printf("Sub thread id: %ld\n", sub_thread_id);

    while(1)
    {
        sleep(1);
        printf("Sub Thread is running!\n");
    }
}

int main()
{
    // 쓰레드 구조체 선언
    pthread_t sub_thread;

    pthread_t main_thread_id = pthread_self();
    printf("Main thread ID : %ld\n", main_thread_id);

    // 쓰레드 생성
    int ret;
    ret = pthread_create(&sub_thread, NULL, sub_thread_main, NULL);
    if(ret != 0)
    {
        printf("Fail to create a sub thread\n");
        return 0;
    }

    // main thread end
    printf("Main thread End.\nSub Thread ID : %ld\n", sub_thread);
    pthread_exit(0);
}