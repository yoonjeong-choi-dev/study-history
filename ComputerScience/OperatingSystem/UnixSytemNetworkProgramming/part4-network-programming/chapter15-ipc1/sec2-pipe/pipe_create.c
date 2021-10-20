#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 32

int main()
{
    // 입출력 버퍼 및 파일 기술어 정의
    char putMsg[BUFFER_SIZE], getMsg[BUFFER_SIZE];
    int pipeDescriptors[2];

    // 파이프 생성
    if(pipe(pipeDescriptors) == -1)
    {
        printf("Fail to create a pipe\n");
        return 0;
    }

    // 파이프에 넣을 메시지 작성
    sprintf(putMsg, "From input pipe");
    printf("Input pipe message : %s\n", putMsg);
    write(pipeDescriptors[1], putMsg, BUFFER_SIZE);

    // 파이프에서 메시지 읽어오기
    read(pipeDescriptors[0], getMsg, BUFFER_SIZE);
    printf("Output Pipe message : %s\n", getMsg);

    return 1;
}