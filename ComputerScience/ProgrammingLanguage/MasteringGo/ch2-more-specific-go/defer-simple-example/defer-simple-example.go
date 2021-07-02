package main

import "fmt"

func example1() {
	for i := 3; i > 0; i-- {
		defer fmt.Print(i, " ")
	}
}

func example2() {
	for i := 3; i > 0; i-- {
		// defer에서 지정한 익명함수는 해당 코드 블록이 끝난 후 평가 => i는 0으로 저장되어 있음
		defer func() {
			fmt.Print(i, " ")
		}()
	}
}

func example3() {
	for i := 3; i > 0; i-- {
		defer func(n int) {
			fmt.Print(n, " ")
		}(i)
	}
}

func main() {
	fmt.Println("단순한 fmt 함수 지연")
	example1()
	fmt.Println()

	fmt.Println("내부에서 i를 호출하는 익명 함수 지연")
	example2()
	fmt.Println()

	fmt.Println("i를 인자로 받는 함수 지연")
	example3()
	fmt.Println()
}
