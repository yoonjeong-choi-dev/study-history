#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

void print_file_stat(struct stat file_stat);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n\n", argv[0]);
        return -1;
    }

    struct stat file_stat;
    if (stat(argv[1], &file_stat) == 0)
    {
        printf("File: %s", argv[1]);
        print_file_stat(file_stat);
    }
    else
    {
        printf("Unable to get file properties with stat()\n");
        printf("Check the file : %s\n", argv[1]);
    }

    return 0;
}

void print_file_stat(struct stat file_stat)
{
    // i-node 번호
    printf("\nFile Inode : %ld", file_stat.st_ino);

    // 파일 모드
    printf("\nFile access: ");
    if (file_stat.st_mode & R_OK)
        printf("read ");
    if (file_stat.st_mode & W_OK)
        printf("write ");
    if (file_stat.st_mode & X_OK)
        printf("execute");

    // 파일 사이즈
    printf("\nFile size: %ld", file_stat.st_size);

    // 파일 최종 접근, 변경, 수정 시간
    struct tm dt;
    dt = *(gmtime(&file_stat.st_atime));
    printf("\nAccessed on: %d-%d-%d %d:%d:%d", dt.tm_year + 1900, dt.tm_mon, dt.tm_mday,
           dt.tm_hour, dt.tm_min, dt.tm_sec);

    dt = *(gmtime(&file_stat.st_mtime));
    printf("\nModified on: %d-%d-%d %d:%d:%d", dt.tm_year + 1900, dt.tm_mon, dt.tm_mday,
           dt.tm_hour, dt.tm_min, dt.tm_sec);

    dt = *(gmtime(&file_stat.st_ctime));
    printf("\nChanged on: %d-%d-%d %d:%d:%d", dt.tm_year + 1900, dt.tm_mon, dt.tm_mday,
           dt.tm_hour, dt.tm_min, dt.tm_sec);

    printf("\n");
}