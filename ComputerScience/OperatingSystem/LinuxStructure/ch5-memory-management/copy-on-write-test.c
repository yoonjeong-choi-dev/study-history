#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#define BUFFER_SIZE (100 * 1024 * 1024)
#define PAGE_SIZE 4096
#define COMMAND_SIZE 4096

static char *p;
static char command[COMMAND_SIZE];

static void child_fn(char *p){
    printf("*** child process info before memory access ***:\n");
    fflush(stdout);

    // 자식 프로세스 메모리 정보(시스템, 가상, 물리, 페이징 폴트) 출력
    snprintf(command, COMMAND_SIZE,
        "ps -o pid,comm,vsz,rss,min_flt,maj_flt | grep '^ *%d'", getpid());
    system(command);
    
    // 자식 프로세스 메모리 통계 출력
    printf("*** free memory info before memory access ***:\n");
	fflush(stdout);
	system("free");

    // 확보한 모든 페이지에 접근
    int i;
    for(i=0;i<BUFFER_SIZE;i+=PAGE_SIZE){
        p[i] = 0;
    }

    // 자식 프로세스 메모리 정보(시스템, 가상, 물리, 페이징 폴트) 출력
    printf("*** child process info after memory access ***:\n");
    fflush(stdout);
    system(command);

    // 자식 프로세스 메모리 통계 출력
    printf("*** free memory info after memory access ***:\n");
	fflush(stdout);
	system("free");

    exit(EXIT_SUCCESS);
    
}

static void parent_fn(void){
    // 자식 프로세스 종료까지 대기
    wait(NULL);

    exit(EXIT_SUCCESS);
}

int main(void){
    char *buf;
    p = malloc(BUFFER_SIZE);
    if(p==NULL)
        err(EXIT_FAILURE, "malloc() failed");

    // 페이지 접근
    int i;
    for(i=0;i<BUFFER_SIZE;i+=PAGE_SIZE){
        p[i] = 0;
    }

    // 프로세스 fork 이전 메모리 통계 출력
    printf("*** free memory info before fork() ***:\n");
    fflush(stdout);
    system("free");

    // 자식 프로세스 생성
    pid_t ret;
    ret = fork();
    if (ret == -1)
        err(EXIT_FAILURE, "fork() failed");

    // 자식 프로세스인 경우
    if (ret == 0)
        child_fn(p);
    // 부모 프로세스인 경우
    else
        parent_fn();

    // never 
    err(EXIT_FAILURE, "shouldn't reach hear");
}