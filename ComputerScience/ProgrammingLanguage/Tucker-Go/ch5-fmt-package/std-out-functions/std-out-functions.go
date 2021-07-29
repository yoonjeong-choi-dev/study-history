package main

import "fmt"

func main() {
	var a int = 10
	var b int = 20
	var f float64 = 132456789.1234

	fmt.Print("a:", a, "b:", b)
	fmt.Println("a:", a, "b", b, "f", f)
	fmt.Printf("a: %d b: %d f: %f\n", a, b, f)
}
