#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// subthread function
void* sub_thread_main(void* arg)
{
    printf("Sub Thread is running!\n");
    sleep(1);
    printf("Sub Thread is done\n");
    pthread_exit((void*)1);
}

int main()
{
    // 쓰레드 구조체 선언
    pthread_t sub_thread;
    int sub_thread_ret;

    // 쓰레드 생성
    int ret;
    ret = pthread_create(&sub_thread, NULL, sub_thread_main, NULL);
    if(ret != 0)
    {
        printf("Fail to create a sub thread\n");
        return 0;
    }

    // Wait Sub thread
    pthread_join(sub_thread, (void **)&sub_thread_ret);

    // print the result of sub thread
    printf("Sub thread result : %d\n", sub_thread_ret);
    return 1;
}