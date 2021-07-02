package main

//#include <stdio.h>
//void callC() {
//	printf("Calling C-code!\n");
//}
import "C"

import "fmt"

// vscode말고 cli창에서 실행시켜야 한다
func main() {
	fmt.Println("A Go Statement!")

	// import "C" 위의 주석들을 C코드로 인식
	C.callC()

	fmt.Println("Another Go Statement!")
}
