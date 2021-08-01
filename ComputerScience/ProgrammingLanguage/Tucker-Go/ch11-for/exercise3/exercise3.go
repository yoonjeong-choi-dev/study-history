package main

import "fmt"

func main() {
	for i := 1; i < 10; i += 2 {
		fmt.Printf("%d * %d = %d\n", i, i, i*i)
	}
}
