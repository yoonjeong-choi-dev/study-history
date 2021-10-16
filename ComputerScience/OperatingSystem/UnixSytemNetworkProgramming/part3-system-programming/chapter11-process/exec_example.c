#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("ls -alF를 실행합니다.\n");

    // execl 실행 파일 경로와 인수들을 인자로 받는다
    execl("/usr/bin/ls", "ls", "-alF", (char*)0);

    // 실패 시 다음 문장이 실행 => 에러 확인
    printf("에러 발생\n");

    return 0;
}