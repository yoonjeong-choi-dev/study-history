#include <stdio.h>

#include <fcntl.h>

// 파일을 읽고 쓸 버퍼 사이즈 정의
#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <file_name>\n\n", argv[0]);
        return -1;
    }

    // open, read을 위한 변수들 지정
    int read_count, write_count;
    int read_file, tty_file;
    char buffer[BUFFER_SIZE];

    // 읽을 파일 open
    read_file = open(argv[1], O_RDONLY);
    if (read_file < 0)
    {
        printf("%s file open failed\n", argv[1]);
        return -1;
    }

    // 출력을 위한 특수 파일 tty open
    tty_file = open("/dev/tty", O_WRONLY);
    if (tty_file < 0)
    {
        printf("/dev/tty file open failed\n");
        return -1;
    }

    // tty에 읽을 파일의 데이터를 write i.e 출력
    do
    {
        read_count = read(read_file, buffer, BUFFER_SIZE);
        write_count = write(tty_file, buffer, read_count);
    } while (read_count > 0);

    // 리소스 정리
    close(read_file);
    close(tty_file);

    return 0;
}