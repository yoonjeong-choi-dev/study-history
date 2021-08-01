package main

import "fmt"

func getMyAge() (int, bool) {
	return 29, true
}

func main() {
	if age, ok := getMyAge(); ok && age < 20 {
		fmt.Println("You are young", age)
	} else if ok && age < 30 {
		fmt.Println("Nice age", age)
	} else if ok {
		fmt.Println("You are beautiful", age)
	} else {
		fmt.Println("Init function error")
	}
}
