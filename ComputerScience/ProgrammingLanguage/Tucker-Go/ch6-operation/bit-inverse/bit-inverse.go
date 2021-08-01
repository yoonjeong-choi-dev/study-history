package main

import "fmt"

func main() {
	var x1 int8 = 34
	var x2 int16 = 34
	var x3 uint8 = 34
	var x4 uint16 = 32

	fmt.Printf("int8  : ^%d = %5d,\t%08b, %08b\n", x1, ^x1, uint8(x1), uint8(^x1))
	fmt.Printf("int16 : ^%d = %5d,\t%016b, %016b\n", x2, ^x2, uint16(x2), uint16(^x2))
	fmt.Printf("uint8 : ^%d = %5d,\t%08b, %08b\n", x3, ^x3, x3, ^x3)
	fmt.Printf("uint16: ^%d = %5d,\t%016b, %016b\n", x4, ^x4, x4, ^x4)
}
