package main

import (
	"fmt"
	"unsafe"
)

func main() {
	array := [...]int{0, 1, 2, 3, 4}
	pointer := &array[0]
	fmt.Print("*pointer(=&array[0]) : ", *pointer)

	// unsafe를 통해 c와 같이 포인터 이동을 통한 메모리 접근 가능
	memoryAddr := uintptr(unsafe.Pointer(pointer)) + unsafe.Sizeof(array[0])

	for i := 0; i < len(array); i++ {
		pointer = (*int)(unsafe.Pointer(memoryAddr))
		fmt.Println("*pointer+(", i+1, ") :", *pointer)
		memoryAddr = uintptr(unsafe.Pointer(pointer)) + unsafe.Sizeof(array[0])
	}
}
