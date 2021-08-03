package main

import "fmt"

func main() {
	var a int = 50
	var pa *int

	pa = &a

	fmt.Printf("value of pa : %p\n", pa)
	fmt.Printf("value at pa : %d\n", *pa)

	*pa = 123
	fmt.Printf("value of a : %d\n", a)
}
