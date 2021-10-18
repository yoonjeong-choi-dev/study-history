#include <iostream>
#include <pthread.h>

// sleep() 함수 선언
extern "C"
{
    int sleep(int);
}

// 스레드를 생성하고 사용하는 클래스
class ThreadHandler
{
public:
    // 스레드 생성 및 스레드에서 동작하는 함수 정의
    bool MakeThread();
    static void* RunThread(void *arg);

    // 스레드가 돌아가는지 여부를 관리하는 함수들
    bool IsRun() { return _isRun; }
    void SetIsRun(bool val) { _isRun = true; }

private:
    bool _isRun;
    pthread_t _thread;
};

bool ThreadHandler::MakeThread()
{
    int resultCreation = pthread_create(&_thread, NULL, ThreadHandler::RunThread, NULL);
    if(resultCreation != 0)
    {
        std::cout << "Fail to create a thread"<<std::endl;
        return false;
    }

    return true;
}

void* ThreadHandler::RunThread(void *arg)
{
    while(1)
    {
        std::cout << "Thread is running" <<std::endl;
        sleep(1);
    }

    return NULL;
}


int main()
{
    ThreadHandler* threadHanlder = new ThreadHandler();

    // 스레드 생성
    if(threadHanlder->MakeThread())
    {
        threadHanlder->SetIsRun(true);
    }
    else
    {
        threadHanlder->SetIsRun(false);
    }

    pthread_exit(0);
}