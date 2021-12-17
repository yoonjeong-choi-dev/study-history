package main

import "fmt"

func square(x int) int {
	return x * x
}

func main() {
	fmt.Printf("%d * %d = %d\n", 9, 9, square(9))
}
