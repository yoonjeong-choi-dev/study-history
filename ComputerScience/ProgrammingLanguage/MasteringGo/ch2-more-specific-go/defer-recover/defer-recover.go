package main

import "fmt"

func recoverByDefer() {
	fmt.Println("recoverByDefer start!")
	defer func() {
		if c := recover(); c != nil {
			fmt.Println("Recover inside this function!")
		}
	}()

	fmt.Println("About to call 'panicFunc' to generate Panic!!")
	panicFunc()
	fmt.Println("'panicFunc' generated PANIC!!!")
	fmt.Println("'recoverByDefer ended...")
}

func panicFunc() {
	fmt.Println("panicFunc start!")
	panic("Panic in this function!")
}

func main() {
	recoverByDefer()
	fmt.Println("main() ended!")
}
