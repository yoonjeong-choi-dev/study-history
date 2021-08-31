#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#define BUFFER_SIZE 1000
#define ALLOC_SIZE (100 * 1024 * 1024)

static char command[BUFFER_SIZE];
static char file_contents[BUFFER_SIZE];
static char overwirte_data[] = "HELLO";
static const char FILE_NAME[] = "file-map-test-file";

int main(void)
{
    pid_t pid;
    pid = getpid();

    // 프로세스의 메모리 맵 정보를 터미널 창에 출력하는 명령어 저장
    snprintf(command, BUFFER_SIZE, "cat /proc/%d/maps", pid);

    puts("*** memory map before allocation ***");
    fflush(stdout);
    // system : 첫번째 파라미터에 지정된 명령어를 리눅스 시스템에 실행
    system(command);

    // 파일 접근
    int fd;
    fd = open(FILE_NAME, O_RDWR);
    if (fd == -1)
    {
        err(EXIT_FAILURE, "open() failed");
    }

    // 파일을 메모리 공간에 매핑
    char *file_contents;
    file_contents = mmap(NULL, ALLOC_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (file_contents == (void *)-1)
    {
        warn("mmap() failed");
        goto close_file;
    }

    // 매핑 후 메모리 맵 정보 출력
    puts("");
    printf("*** succeeded to allocate memory: address = %p; size= 0x%x ***\n", file_contents, ALLOC_SIZE);
    puts("*** memory map after allocation ***");
    fflush(stdout);
    system(command);

    // 매핑된 영역의 데이터를 읽어서 출력
    puts("");
    printf("*** file contents before overwrite mapped region : %s", file_contents);

    // 매핑된 영역의 데이터 오버라이트
    memcpy(file_contents, overwirte_data, strlen(overwirte_data));
    puts("");
    printf("*** file contents after overwrite mapped region : %s", file_contents);

    // 메핑된 메모리 해제
    if (munmap(file_contents, ALLOC_SIZE) == -1){
        err(EXIT_FAILURE, "mumap() failed");
    }

close_file:
    if (close(fd) == -1)
        warn("close() failed");
    exit(EXIT_SUCCESS);
}