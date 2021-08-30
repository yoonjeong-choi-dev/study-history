#include <stdio.h>
#include <stdlib.h>

int main(void){
    int *p = NULL;
    puts("before invalid access");

    // 잘못된 주소(널)에 접근
    *p = 0;

    puts("after invalid access");

    exit(EXIT_SUCCESS);
}