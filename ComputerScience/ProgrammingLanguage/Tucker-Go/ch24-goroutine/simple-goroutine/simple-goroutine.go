package main

import (
	"fmt"
	"time"
)

func PrintKoeran() {
	koreans := []rune{'가', '나', '다', '라', '마'}

	for _, c := range koreans {
		time.Sleep(300 * time.Millisecond)
		fmt.Printf("%c\n", c)
	}
}

func PrintNumber() {
	for i := 1; i <= 5; i++ {
		time.Sleep(500 * time.Millisecond)
		fmt.Printf("%d\n", i)
	}
}

func main() {
	go PrintKoeran()
	go PrintNumber()

	time.Sleep(3 * time.Second)
}
