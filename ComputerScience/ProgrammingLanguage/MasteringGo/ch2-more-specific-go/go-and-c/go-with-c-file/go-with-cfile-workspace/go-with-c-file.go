package main

// #cgo CFLAGS: -I${SRCDIR}/myCLib
// #cgo LDFLAGS: ${SRCDIR}/callC.a
// #include <stdlib.h>
// #include <callC.h>
import "C"

import (
	"fmt"
	"unsafe"
)

func main() {
	fmt.Println("Going to call a function from c-files!")
	C.cHello()

	fmt.Println("Going to call another function from c-files!")

	// C.CString 함수를 통해 C언어용 문자열 생성 => defer를 통해 해당 메모리 해제
	myGoMessage := "This is YJ!"
	myCMessage := C.CString(myGoMessage)
	defer C.free(unsafe.Pointer(myCMessage))

	C.printMessage(myCMessage)
	fmt.Println("All done perfectly!!!")
}
