#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main()
{
    // 세마포어와 파일을 위한 변수
    int step;
    int semaphore_id, process_id;
    FILE *file;
    struct sembuf semaphore_buf;

    // sembuf 구조체 초기화
    semaphore_buf.sem_flg = SEM_UNDO;
    semaphore_buf.sem_num = 0; // 세마포어 갯수

    // semget : 세마포어를 새로 생성
    semaphore_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);

    // semclt : 세마포어 제어 i.e 초기화
    // SETVAL : semctl의 마지막 인수로 union semun의 val 설정
    if (semctl(semaphore_id, 0, SETVAL, 1) == -1)
    {
        fprintf(stderr, "Fail to initialize a semaphore\n");
        exit(0);
    }

    printf("Plus Semaphore PID : %d\n", getpid());

    // 파일에 메시지를 5번 기입 후 종료
    for (step = 0; step < 5; step++)
    {
        // 세마포어에 마지막으로 수정을 가한 프로세스의 PID 출력
        // GETPID : 마지막으로 sempos 함수를 실행한 프로세스의 PID 리턴
        process_id = semctl(semaphore_id, 0, GETPID, 0);
        printf("Last Process Id changing semaphore : %d\n", process_id);

        // 파일을 열고 메시지 저장
        file = fopen("./data.txt", "a+");
        fprintf(file, "Plus Semaphore Process Massage\n");
        fclose(file);

        // 세모포어 값을 1 증가시킨뒤 1초 sleep
        semaphore_buf.sem_op = 1;
        if (semop(semaphore_id, &semaphore_buf, 1) == -1)
        {
            fprintf(stderr, "Fail to plus semaphore\n");
            exit(0);
        }
        sleep(1);
    }

    // 세마포어 제거
    // IPC_RMID : 세마포어 삭제
    if (semctl(semaphore_id, 0, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "Fail to remove semaphore\n");
        exit(0);
    }

    exit(1);
}