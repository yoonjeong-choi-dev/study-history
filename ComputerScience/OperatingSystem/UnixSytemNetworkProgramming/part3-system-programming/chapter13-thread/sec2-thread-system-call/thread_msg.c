#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


// 쓰레드에 전달할 구조체 정의
typedef struct {
    char* ip_address;
    char* host_name;
    int port_number;
} IpInfoType;


// subthread function
void* set_connection(void* ip_info)
{
    // 전달받은 void* 데이터 형변환
    IpInfoType* connection = (IpInfoType*)ip_info;

    printf("SetConnection Thread is RUNNING\n");
    printf("IP Address: %s\n", connection->ip_address);
    printf("Hostname : %s\n", connection->host_name);
    printf("Port Number : %d\n", connection->port_number);
    printf("Connect with the system...\n");
    sleep(1);
}

int main()
{
    // 쓰레드 구조체 선언
    pthread_t sub_thread;
    int sub_thread_ret;

    // 쓰레드에 전달할 정보 초기화
    IpInfoType ip_info;
    ip_info.ip_address = "192.168.8.100";
    ip_info.host_name = "yjchoi";
    ip_info.port_number = 8080;

    // 쓰레드 생성
    int ret;
    ret = pthread_create(&sub_thread, NULL, set_connection, (void*) &ip_info);
    if(ret != 0)
    {
        printf("Fail to create a sub thread\n");
        return 0;
    }

    pthread_exit(0);
}