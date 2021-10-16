#include <unistd.h>
#include <stdio.h>

int main()
{
    // 프로세스 정보들을 저장할 변수
    int pid, uid, gid;

    pid = getpid();
    uid = getuid();
    gid = getgid();

    printf("<< Process Information >>\n");
    printf("PID: %d, User Id(UID): %d, Groud Id(GID): %d\n", pid, uid, gid);

    return 0;
}