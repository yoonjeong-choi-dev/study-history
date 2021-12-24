package main

import (
	"fmt"
	"time"
)

func runSomeLoop(goId, n int) {
	for i := 0; i < 10; i++ {
		fmt.Printf("%d goruotine : %d\n", goId, i)
	}
}

func main() {
	var numWork int = 3
	for i := 0; i < numWork; i++ {
		go runSomeLoop(i, 10)
	}

	time.Sleep(2 * time.Second)

	fmt.Println("Finally... Stop main goroutine")
}
