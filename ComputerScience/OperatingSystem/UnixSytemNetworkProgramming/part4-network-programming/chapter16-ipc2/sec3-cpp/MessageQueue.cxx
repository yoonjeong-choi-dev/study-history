#include <iostream>

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "MessageQueue.h"

using namespace std;

// MessageQueue 클래스 메서드 정의
// 수신 스레드 생성 : 메시지 큐의 키값을 얻은 후, 스레드 실행
bool MessageQueue::RunReciever()
{
    int resultCreation;
    
    resultCreation = pthread_create(&recieverThread, NULL, MessageQueue::ReadMessageQueue, NULL);
    if (resultCreation != 0)
    {
        std::cout << "Fail to create the Reciever thread" << std::endl;
        return false;
    }

    cout << "<<< Success to create Reciever Thread >>>"<<endl;
    return true;
}

// 수신 스레드의 메인 함수
void *MessageQueue::ReadMessageQueue(void *_arg)
{
    // 메시지 큐의 키
    int queueKey = GetMessageQueueKey();
    if (queueKey <= 0)
    {
        cout << "MessageQueue::ReadMessageQueue() : Invalid Message Queue Key" << endl;
        return NULL;
    }

    // 메시지 큐에서 사용할 변수 선언
    int messageQ_id;
    DataType data_type;
    long int msg_type = GetMessageType();
    int result;

    // 메시지 큐 생성 및 큐의 ID 획득
    messageQ_id = msgget((key_t)queueKey, 0666 | IPC_CREAT);
    if (messageQ_id == -1)
    {
        cout << "ReadMessageQueue : Fail to create message queue, Error No : " << errno << endl;
        return NULL;
    }
    cout << "\n\n<< Reciever Process >>\n" << endl;

    // main process : quit 메시지 올 때까지 계속 실행
    while (1)
    {
        result = msgrcv(messageQ_id, (void *)&data_type, DATA_SIZE, msg_type, 0);
        if (result == -1)
        {
            cout << "ReadMessageQueue : Fail to read message queue, Error No : " << errno << endl;
            return NULL;
        }

        if (strlen(data_type.user_number) == 4 && !strncmp(data_type.user_number, "quit", 4))
        {
            cout << "Quit Reciever Process" << endl;
            break;
        }

        cout << "<< Recieved User Info >>" << endl;
        cout << "User No : " << data_type.user_number << endl;
        cout << "User password : " << data_type.password << endl;
        cout << "User Phone Number : " << data_type.phone_number << endl;
    }

    // 메시지 큐 제거
    result = msgctl(messageQ_id, IPC_RMID, 0);
    if (result == -1)
    {
        cout << "ReadMessageQueue : Fail to remove message queue" << endl;
        return NULL;
    }

    return NULL;
}

// 송신 스레드 : Write Message Queue
bool MessageQueue::RunSender()
{
    int resultCreation;
    resultCreation = pthread_create(&senderThread, NULL, MessageQueue::WriteMessageQueue, NULL);
    if (resultCreation != 0)
    {
        std::cout << "Fail to create the Sender thread" << std::endl;
        return false;
    }

    cout << "<<< Success to create Sender Thread >>>"<<endl;
    return true;
}

// 송신 스레드 메인 함수
void *MessageQueue::WriteMessageQueue(void *_arg)
{
    // 메시지 큐의 키
    int queueKey = GetMessageQueueKey();
    if (queueKey <= 0)
    {
        cout << "MessageQueue::WriteMessageQueue() : Invalid Message Queue Key" << endl;
        return NULL;
    }

    // 메시지 큐에서 사용할 변수 선언
    int messageQ_id;
    DataType data_type;
    long int msg_type = GetMessageType();
    int result;
    char buffer[14];
    int is_run = 1;

    // reciever에서 생성한 큐의 ID 획득
    messageQ_id = msgget((key_t)queueKey, 0666 | IPC_CREAT);
    if (messageQ_id == -1)
    {
        cout << "ReadMessageQueue : Fail to get message queue, Error No : " << errno << endl;
        return NULL;
    }

    cout << "\n\n<< Sender Process >>\n" << endl;

    // main process : quit 메시지 올 때까지 계속 실행
    while (is_run)
    {
        // 메시지 구조체 초기화 및 작성
        cout << "<< Enter User Info >>" << endl;
        memset(&data_type, '\0', DATA_SIZE);
        data_type.msg_type = msg_type;

        cout << "User No('quit' to Quit) : ";
        cin >> buffer;
        strncpy(data_type.user_number, buffer, 13);

        // quit 입력 시, 종료
        if (strlen(data_type.user_number) == 4 && !strncmp(data_type.user_number, "quit", 4))
        {
            strncpy(data_type.password, "quit", 4);
            strncpy(data_type.phone_number, "quit", 4);
            is_run = 0;
        }
        else
        {
            cout << "User Password : ";
            cin >> buffer;
            strncpy(data_type.password, buffer, 8);

            cout << "User Phone Number : ";
            cin >> buffer;
            strncpy(data_type.phone_number, buffer, 8);
        }

        // 메시지 전송
        result = msgsnd(messageQ_id, (void *)&data_type, DATA_SIZE, 0);
        if (result == -1)
        {
            cout << "ReadMessageQueue : Fail to write message queue, Error No :" << errno << endl;
            return NULL;
        }

        if (is_run == 0)
        {
            cout << "Quit Sender Process" << endl;
        }
    }

    return NULL;
}

// 메시지 큐의 키값을 얻는 메서드
int MessageQueue::GetMessageQueueKey()
{
    return 9999;
}

// 서로 주고 받을 메시지 종류를 얻는 메서드
long int MessageQueue::GetMessageType()
{
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage : " << argv[0] << "< send | recv > " << endl
             << endl;
        return 0;
    }

    // 메시지 큐 객체 생성
    MessageQueue *msgQ = new MessageQueue();

    if (!strncmp(argv[1], "send", 4))
    {
        cout << "\n\n<<< Create Sender Thread >>>" << endl;
        if (msgQ->RunSender() == false)
        {
            cout << "Fail to Run Sender Thread" << endl;
            return 0;
        }
    }
    else if (!strncmp(argv[1], "recv", 4))
    {
        cout << "\n\n<<< Create Reciever Thread >>>" << endl;
        if (msgQ->RunReciever() == false)
        {
            cout << "Fail to Run Reciever Thread" << endl;
            return 0;
        }
    }
    else
    {
        cout << "Usage : " << argv[0] << "< send | recv > " << endl
             << endl;
        delete msgQ;
        return 0;
    }

    // 메인 스레드 종료
    pthread_exit(0);
    return 0;
}