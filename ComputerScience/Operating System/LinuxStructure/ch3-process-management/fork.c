#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

// 자식 프로세스 pid 출력
static void child(){
    printf("I'm child! my pid is %d.\n", getpid());
    exit(EXIT_SUCCESS);
}

// 부모 프로세스 pid 출력
static void parent(pid_t pid_c){
    printf("I'm parent! my pid is %d and the pid of my child is %d\n", getpid(), pid_c);
    exit(EXIT_SUCCESS);
}

int main(void){
    // fork는 부모 프로세스의 경우 자식 프로세스 id를, 자식 프로세스는 0을 반환
    pid_t ret;
    ret = fork();

    // 포크 실패
    if (ret==-1){
        err(EXIT_FAILURE, "fork() failed");
    }

    if (ret == 0){
        // fork()는 자식 프로세스에 대해서는 0 반환
        // => 자식 프로세스 정보 출력
        child();
    }
    else{
        // 부모 프로세스의 경우 자식 프로세스 id 반환
        parent(ret);
    }

    // 올 수 없는 부분
    err(EXIT_FAILURE, "shouldn't reach here");
}