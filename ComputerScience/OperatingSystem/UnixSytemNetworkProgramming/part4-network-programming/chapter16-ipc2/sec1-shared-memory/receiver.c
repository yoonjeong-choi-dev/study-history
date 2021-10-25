#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// 공유 메모리 키 값과 사이즈 선언
#define SHARED_MEM_ID 9000
#define SHARED_MEM_SIZE 64

int main()
{
    // 공유 메모리 사용을 위한 변수 선언
    struct shmid_ds buf;
    void *shared_memory = (void *) 0;
    int shared_memory_id;
    char *buffer;
    int buffer_len;
    int is_run = 1;

    // Step 1: 공유 메모리 확보(with 생성)
    shared_memory_id = shmget((key_t)SHARED_MEM_ID, SHARED_MEM_SIZE, 0666|IPC_CREAT);
    if(shared_memory_id == -1)
    {
        printf("shmget : Fail to create shared memory\n");
        return 0;
    }

    // Step 2: 공유 메모리와 프로세스 메모리 연결
    shared_memory = shmat(shared_memory_id, (void*) 0, 0);
    if (shared_memory == (void*)-1)
    {
        printf("shmat : Fail to load shared memory on the process memroy\n");
        return 0;
    }

    // Step 3: 버퍼와 연결된 메모리 연결
    buffer = (char*) shared_memory;
    
    // 버퍼 사이즈 받아오기
    shmctl((key_t)SHARED_MEM_ID, IPC_STAT, &buf);
    buffer_len = (int) buf.shm_segsz / sizeof(char);

    printf("<< Reciever Process >>\n");
    printf("SHARED MEMORY LOADED - length : %d\n", buffer_len);
    // 프로세스 실행
    while(is_run)
    {
        // 첫 2바이트 플래그가 ON인 경우, 메시지 읽고 플래그 NO로 변경
        if(!strncmp(buffer, "ON", 2))
        {
            printf("Message Read: %s\n", buffer+2);
            strncpy(buffer, "NO", 2);

            // 플래그 제외 quit인 경우 프로세스 종료
            if(strnlen(buffer, buffer_len) == 6 && !strncmp(buffer+2, "quit", 4))
            {
                is_run = 0;
            }
        }

        // 0.01초간 휴식 : cpu 점령 방지용
        usleep(10000);
    }

    // 공유 메모리를 프로세스에서 분리
    if(shmdt(shared_memory) == -1)
    {
        printf("shmdt : Fail to free shared memory from the process memory\n");
        return 0;
    }

    // 공유 메모리 제거
    if(shmctl(shared_memory_id, IPC_RMID, 0) == -1)
    {
        printf("shmctl : Fail to delete shared memory\n");
    }

    return 1;
}