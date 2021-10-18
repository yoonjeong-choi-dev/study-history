#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// 쓰레드에 전달할 구조체 정의
typedef struct {
    char* ip_address;
    char* host_name;
    int port_number;
} IpInfoType;

// 쓰레드에서 할당할 전역 포트 번호 => 동시 접근 시 문제 발생
int count_number = 0;

// 뮤텍스 선언
pthread_mutex_t get_ip_info_mutex = PTHREAD_MUTEX_INITIALIZER;

// IP 정보를 할당
IpInfoType get_ip_info()
{

    int mutex_ret;

    // 카운트 증가 : 뮤텍스 잠금 시작
    mutex_ret = pthread_mutex_lock(&get_ip_info_mutex);
    count_number++;
    sleep(3);

    // IP 정보 초기화
    IpInfoType ip_info ;
    ip_info.ip_address = "192.168.8.100";
    ip_info.host_name = "yjchoi";
    ip_info.port_number = count_number;

    // 뮤텍스 해제
    mutex_ret = pthread_mutex_unlock(&get_ip_info_mutex);

    return ip_info;
}


// subthread function
void* set_connection(void* arg)
{
    IpInfoType ip_info;

    printf("SetConnection Thread is RUNNING\n");

    // 서브 쓰레드 주요 프로세스
    while(1)
    {
        ip_info = get_ip_info();
        printf("Sub Thread Port Number : %d\n", ip_info.port_number);
        sleep(1);
    }
}

int main()
{
    // 메인 스레드에서 할당받을 IP 정보 구조체
    IpInfoType main_ip_info;

    // 쓰레드 구조체 선언
    pthread_t sub_thread;

    // 쓰레드 생성
    int ret;
    ret = pthread_create(&sub_thread, NULL, set_connection, NULL);
    if(ret != 0)
    {
        printf("Fail to create a sub thread\n");
        return 0;
    }

    // 메인 쓰레드 주요 프로세스
    while (1)
    {
        main_ip_info = get_ip_info();
        printf("Main Thread Port Number : %d\n", main_ip_info.port_number);
        sleep(1);
    }
    
}