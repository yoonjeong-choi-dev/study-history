package main

import (
	"fmt"
	"math"
)

func compareFloat(a, b float64) bool {
	const epsilon = 0.000001

	diff := a - b
	if diff < epsilon || -diff < epsilon {
		return true
	} else {
		return false
	}
}

func compareFloatWithOneBit(a, b float64) bool {

	// Nextafter(a, b) : a->b로 변하기 위해 변경해야하는 가장 마지막 비트수 변경
	// 두 값이 같으면, a-b는 맨 마지막 비트 한개만 차이나는 것을 의미
	return math.Nextafter(a, b) == b
}

func main() {
	var a float64 = 0.1
	var b float64 = 0.2
	var c float64 = 0.3

	fmt.Printf("%0.18f + %0.18f = %0.18f\n", a, b, a+b)
	fmt.Printf("Simple way - %0.18f == %0.18f : %v\n", c, a+b, compareFloat(a+b, c))
	fmt.Printf("Nextafter  - %0.18f == %0.18f : %v\n", c, a+b, compareFloatWithOneBit(a+b, c))

	a = 0.0000000000004
	b = 0.0000000000002
	c = 0.0000000000007
	fmt.Printf("%g == %g : %v\n", c, a+b, compareFloat(a+b, c))
	fmt.Printf("Simple way - %g == %g : %v\n", c, a+b, compareFloat(a+b, c))
	fmt.Printf("Nextafter  - %g == %g : %v\n", c, a+b, compareFloatWithOneBit(a+b, c))
}
