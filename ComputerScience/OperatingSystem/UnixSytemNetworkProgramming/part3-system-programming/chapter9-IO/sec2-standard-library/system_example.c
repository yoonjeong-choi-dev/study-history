#include <stdio.h>

int main()
{
    int ret;

    printf("배시 실행 : ls -l\n");

    printf("=========================================\n");
    ret = system("ls -l");
    printf("=========================================\n");
    
    printf("실행 결과 : %d\n", ret);

    return 0;
}