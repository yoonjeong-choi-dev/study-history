#include <stdio.h>

#include <fcntl.h>

// 파일을 read/write 하기 위한 버퍼 사이즈
#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <source_filename> <new_filename> \n\n", argv[0]);
        return -1;
    }

    // open, read, write을 위한 변수들 지정
    int read_count, write_count, source_file, new_file;
    char buffer[BUFFER_SIZE];

    // 복사할 파일 열기
    source_file = open(argv[1], O_RDONLY);

    // 복사를 위한 파일 생성
    new_file = open(argv[2], O_WRONLY | O_CREAT | O_APPEND);

    if (source_file < 0 || new_file < 0)
    {
        printf("File open failed\n");
        printf("File Decsriptor : source_file=%d, new_file=%d\n", source_file, new_file);
        return -1;
    }

    // 생성된 파일에 읽기 모드 추가
    if(chmod(argv[2], 0664) < 0)
    {
        printf("File mode change error\n");
        close(source_file);
        close(new_file);

        return -1;
    }

    // 복사할 파일을 끝까지 읽어서 생성한 파일에 저장
    do
    {
        read_count = read(source_file, buffer, BUFFER_SIZE);
        write_count = write(new_file, buffer, read_count);
        printf("read_count: %d, write_count: %d\n", read_count, write_count);
    } while (read_count > 0);

    close(source_file);
    close(new_file);

    return 0;
}