package main

import "fmt"

func main() {
	a := 123
	b := 456
	c := 123456789

	fmt.Println("Example1 : 최소너비보다 짧은 정수")
	fmt.Println("%5d, %5d : 공백 생성")
	fmt.Printf("%5d, %5d\n", a, b)
	fmt.Println("%05d, %05d : 공백 채우기")
	fmt.Printf("%05d, %05d\n", a, b)
	fmt.Println("%-5d, %-5d : 왼쪽 정렬")
	fmt.Printf("%-5d, %-5d\n", a, b)

	fmt.Println("Example2 : 최소너비보다 긴 정수")
	fmt.Println("%5d, %5d : 공백 생성")
	fmt.Printf("%5d, %5d\n", c, c)
	fmt.Println("%05d, %05d : 공백 채우기")
	fmt.Printf("%05d, %05d\n", c, c)
	fmt.Println("%-5d, %-5d : 왼쪽 정렬")
	fmt.Printf("%-5d, %-5d\n", c, c)
}
