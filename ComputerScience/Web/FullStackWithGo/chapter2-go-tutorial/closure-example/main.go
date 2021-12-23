package main

import "fmt"

func adderClosure() func(int) int {
	// 클로저에서 참조하는 변수
	var sum int = 0
	return func(x int) int {
		sum += x
		return sum
	}
}

func main() {
	sumClosure := adderClosure()
	fmt.Println("클로저 예시 : 1~10 합")
	for i := 1; i <= 10; i++ {
		fmt.Printf("%d step result : %d\n", i, sumClosure(i))
	}
}
