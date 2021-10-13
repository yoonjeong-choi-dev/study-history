#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filename> \n\n", argv[0]);
        return -1;
    }

    FILE* pfile = fopen(argv[1], "w");
    if (pfile == NULL)
    {
        printf("%s file open failed\n", argv[1]);
        return -1;
    }

    fprintf(stdout, "main() 함수가 실행되었습니다.\n");
    fprintf(stdout, "첫번째 로그는 일반적인 로그입니다.\n");
    fprintf(pfile, "[INFO] 첫번째 로그\n");

    fprintf(stderr, "두번째 로그는 에러입니다\n");
    fprintf(pfile, "[ERROR] 두번째 로그\n");

    fclose(pfile);
    return 0;
}