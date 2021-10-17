#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int process_id;

    if(argc != 2)
    {
        printf("\n\n Usage: %s <PID>\n\n", argv[0]);
        exit(0);
    }

    // 인자로 받은 PID에 시그널 전송
    process_id = atoi(argv[1]);
    kill(process_id, SIGTERM);

    exit(1);
}