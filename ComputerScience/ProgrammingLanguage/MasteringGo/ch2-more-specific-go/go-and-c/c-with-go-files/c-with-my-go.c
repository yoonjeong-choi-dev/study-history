#include <stdio.h>
#include "my-go-lib.h"

int main(int argc, char **argv){

    printf("Going to call a function from g-file!\n");
    PrintMessage();

    // GoInt : Go함수에서 정수 값 넘기고 받아오기 위한 Go용 정수
    GoInt x = 12;
    GoInt y = 23;

    printf("Going to call another function from g-file!\n");
    GoInt ret = Multiply(x, y);
    printf("The result from the Go function : %d\n", (int) ret);
    
    printf("All done perfectly!!!\n");
}