package main

import "fmt"

func fibo1(n int) int {
	if n <= 0 {
		return 0
	}
	if n < 2 {
		return n
	}

	return fibo1(n-1) + fibo1(n-2)
}

func fibo2(n int) int {
	if n <= 0 {
		return 0
	}
	if n < 2 {
		return n
	}

	result := 0
	f1 := 0
	f2 := 1

	for i := 2; i <= n; i++ {
		result = f1 + f2
		f1 = f2
		f2 = result
	}
	return result
}

func main() {
	testNumber := 13

	fmt.Println(fibo1(testNumber))
	fmt.Println(fibo2(testNumber))
}
