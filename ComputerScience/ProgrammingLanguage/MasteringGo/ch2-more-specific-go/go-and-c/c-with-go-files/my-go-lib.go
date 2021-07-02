package main // 반드시 main 패키지여야 한다

import "C"
import "fmt"

//export PrintMessage
func PrintMessage() {
	fmt.Println("Hello~ from Go!")
}

//export Multiply
func Multiply(a, b int) int {
	return a * b
}

func main() {
	// 메인패키지이기 때문에 main 함수는 선언 및 구현해야 한다
}
