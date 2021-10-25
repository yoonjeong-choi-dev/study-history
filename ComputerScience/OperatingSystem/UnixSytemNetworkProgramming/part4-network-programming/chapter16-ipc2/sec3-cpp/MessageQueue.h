#ifndef __MESSAGE_QUEUE_H__
#define __MESSAGE_QUEUE_H__

#include <pthread.h>

// 메시지로 주고 받을 데이터 타입 및 길이 정의
typedef struct 
{
    long int msg_type;          // 메시지 타입
    char user_number[13 + 1];   // 사용자 주민등록 번호
    char password[8+1];         // 사용자 비밀번호
    char phone_number[8 + 1];   // 사용자 핸드폰 번호
} DataType;

#define DATA_SIZE 32            // msg_type을 제외한 구조체 크기(14+9+9)

// 송신, 수신 스데드 관리를 담당하는 클래스
class MessageQueue
{
public:
    // 수신 스레드 : Read Message Queue
    bool RunReciever();
    static void* ReadMessageQueue(void* _arg);

    // 송신 스레드 : Write Message Queue
    bool RunSender();
    static void* WriteMessageQueue(void* _arg);

    // 메시지 큐의 키값을 얻는 메서드
    static int GetMessageQueueKey();

    // 서로 주고 받을 메시지 종류를 얻는 메서드
    static long int GetMessageType();
private:
    // 송신 및 수신 스레드
    pthread_t recieverThread;
    pthread_t senderThread;
};


#endif