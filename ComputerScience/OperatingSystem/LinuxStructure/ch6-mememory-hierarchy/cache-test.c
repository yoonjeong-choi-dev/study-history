#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#define CACHE_LINE_SIZE 64
#define NLOOP (4*1024UL*1024*1024)
#define NSECS_PER_SEC 1000000000UL

/**
 * @brief 
 * - 나노초 단위로 after - before 시간 측정
 * - timespec
 *  - 나노초까지 측정 가능
 *  - tv_sec : 초 단위
 *  - tv_nsec : 나도초 단위
 * 
 * @param before 시작 시간
 * @param after 종료 시간
 * 
 * @return after-before 나노초
 */
static inline long diff_nsec(struct timespec before, struct timespec after)
{

    return (
        (after.tv_sec * NSECS_PER_SEC + after.tv_nsec) -
        (before.tv_sec * NSECS_PER_SEC + before.tv_nsec));
}

int main(int argc, char* argv[]){
    char *program_name;
    program_name = argv[0];

    if(argc!=2){
        fprintf(stderr, "usage: %s <size[KB]>\n", program_name);
        exit(EXIT_FAILURE);
    }

    // CPU 레지스터에 저장
    register int size;
    size = atoi(argv[1]) * 1024;
    if (!size){
        fprintf(stderr, "size should be >=1: %d\n", size);
        exit(EXIT_FAILURE);
    }

    // 입력한 사이즈만큼 메모리 확보
    char* buffer;
    buffer = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if(buffer == NULL)
        err(EXIT_FAILURE, "mmap() failed");

    struct timespec before, after;

    clock_gettime(CLOCK_MONOTONIC, &before);

    // 정해진 횟수(NLOOP) 만큼 확보한 메모리에 대해 시퀀셜 접근
    int i;
    int num_loop = NLOOP / ( size / CACHE_LINE_SIZE);
    for(i=0;i<num_loop; i++){
        long j;
        for(j=0;j<size;j+=CACHE_LINE_SIZE)
            buffer[j] = 0;
    }

    clock_gettime(CLOCK_MONOTONIC, &after);

    printf("%d size average time for once : %f\n", atoi(argv[1]), (double)diff_nsec(before, after)/NLOOP);
    
    // 메모리 해제
    if(munmap(buffer, size) == -1){
        err(EXIT_FAILURE, "munmap() failed");
    }

    exit(EXIT_SUCCESS);
}