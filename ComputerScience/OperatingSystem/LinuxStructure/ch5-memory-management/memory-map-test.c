#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#define BUFFER_SIZE 1000
#define ALLOC_SIZE (100*1024*1024)

static char command[BUFFER_SIZE];

int main(void){
    
    pid_t pid;
    pid = getpid();
    
    // 프로세스의 메모리 맵 정보를 터미널 창에 출력하는 명령어 저장
    snprintf(command, BUFFER_SIZE, "cat /proc/%d/maps", pid);

    puts("*** memory map before allocation ***");
    fflush(stdout);
    // system : 첫번째 파라미터에 지정된 명령어를 리눅스 시스템에 실행
    system(command);


    void* new_memory;
    // mmap : 리눅스 커널에 새로운 메모리를 요구하는 시스템 콜
    new_memory = mmap(NULL, ALLOC_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_memory == (void*) -1){
        err(EXIT_FAILURE, "mmap() failed");
    }

    puts("");
    printf("*** succeeded to allocate memory: address = %p; size= 0x%x ***\n", new_memory, ALLOC_SIZE);
    fflush(stdout);
    system(command);

    // 메모리 해제
    if (munmap(new_memory, ALLOC_SIZE) == -1){
        err(EXIT_FAILURE, "mumap() failed");
    }

    exit(EXIT_SUCCESS);
}