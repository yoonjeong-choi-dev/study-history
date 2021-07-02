#include <stdio.h>
#include "callC.h"

void cHello() {
    printf("Hello~ from C!\n");
}

void printMessage(char* message) {
    printf("Go send me a message : %s\n", message);
}