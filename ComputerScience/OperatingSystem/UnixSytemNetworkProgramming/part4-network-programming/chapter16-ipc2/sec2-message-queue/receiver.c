#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// 사용할 메시지 큐의 키 값 정의
#define MESSAGE_QUEUE_ID 9000

// Step 1: 메시지로 주고 받을 데이터 타입 및 길이 정의
typedef struct
{
    long int msg_type;        // 메시지 타입
    char user_number[13 + 1]; // 사용자 주민등록 번호
    char address[17 + 1];     // 사용자 주소
} UserType;

#define MESSAGE_TYPE 1  // 서로 주고 받을 메시지 종류 정의
#define MESSAGE_SIZE 32 // msg_type을 제외한 구조체 크기(14+18)

int main()
{
    // 메시지 큐에서 사용할 변수 선언
    int messageQ_id, result;
    UserType user_type;
    long int msg_type = MESSAGE_TYPE;

    // Step 2: 메시지 큐 생성 및 큐의 ID 획득
    messageQ_id = msgget((key_t)MESSAGE_QUEUE_ID, 0666 | IPC_CREAT);
    if (messageQ_id == -1)
    {
        printf("msgget : Fail to create message queue, Error No : %d\n", errno);
        return 0;
    }

    printf("\n\n<< Reciever Process >>\n\n");

    // main process : quit 메시지 올 때까지 계속 실행
    while (1)
    {
        // Step 3: 메시지 읽기
        result = msgrcv(messageQ_id, (void *)&user_type, MESSAGE_SIZE, msg_type, 0);
        if (result == -1)
        {
            printf("msgrcv : Fail to read message queue, Error No : %d\n", errno);
            return 0;
        }

        if (strlen(user_type.user_number) == 4 && !strncmp(user_type.user_number, "quit", 4))
        {
            printf("Quit Reciever Process\n");
            break;
        }

        printf("<< Recieved User Info >>\n");
        printf("User No : %s\n", user_type.user_number);
        printf("User Address : %s\n", user_type.address);
    }

    // Step 4 : 메시지 큐 제거
    result = msgctl(messageQ_id, IPC_RMID, 0);
    if (result == -1)
    {
        printf("msgctl : Fail to remove message queue\n");
        return 0;
    }

    return 1;
}