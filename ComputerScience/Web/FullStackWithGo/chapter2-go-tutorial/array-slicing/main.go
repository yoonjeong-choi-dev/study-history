package main

import "fmt"

func main() {
	var origin [5]int = [5]int{1, 2, 3, 4, 5} // 배열
	var sub []int = origin[:3]                // 슬라이스

	fmt.Println("Origin Array :", origin)
	fmt.Println("Sub Array :", sub)

	fmt.Println("Change the sub : sub[1]=7166")
	sub[1] = 7166
	fmt.Println("Origin Array :", origin)
	fmt.Println("Sub Array :", sub)
}
