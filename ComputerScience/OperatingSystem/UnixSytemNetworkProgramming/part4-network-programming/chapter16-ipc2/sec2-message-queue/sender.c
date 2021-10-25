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
    char buffer[17];
    int is_run = 1;

    // Step 2: reciever에서 생성한 큐의 ID 획득
    messageQ_id = msgget((key_t)MESSAGE_QUEUE_ID, 0666 | IPC_CREAT);
    if (messageQ_id == -1)
    {
        printf("msgget : Fail to get message queue, Error No : %d\n", errno);
        return 0;
    }

    printf("\n\n<< Sender Process >>\n\n");

    // main process : quit 메시지 올 때까지 계속 실행
    while (is_run)
    {
        // Step 3: 메시지 구조체 초기화 및 작성
        printf("<< Enter User Info >>\n");
        memset(&user_type, '\0', MESSAGE_SIZE);
        user_type.msg_type = MESSAGE_TYPE;
        
        printf("User No('quit' to Quit) : ");
        gets(buffer);
        strncpy(user_type.user_number, buffer, 13);

        // quit 입력 시, 종료
        if (strlen(user_type.user_number) == 4 && !strncmp(user_type.user_number, "quit", 4))
        {
            strncpy(user_type.address, "quit", 4);
            is_run = 0;
        }
        else
        {
            printf("User Address : ");
            gets(buffer);
            strncpy(user_type.address, buffer, 17);
        }

        // Step 4 : 메시지 전송
        result = msgsnd(messageQ_id, (void *)&user_type, MESSAGE_SIZE, 0);
        if (result == -1)
        {
            printf("msgsnd : Fail to write message queue, Error No : %d\n", errno);
            return 0;
        }

        if(is_run == 0)
        {
            printf("Quit Sender Process\n");
        }
        
    }

    return 1;
}