package main

import "fmt"

const (
	Pig int = iota
	Cow
	Chicken
)

func PrintAnimal(animal int) {
	if animal == Pig {
		fmt.Println("꿀꿀")
	} else if animal == Cow {
		fmt.Println("음메")
	} else if animal == Chicken {
		fmt.Println("꼬끼오")
	} else {
		fmt.Println("....?")
	}
}

func main() {
	PrintAnimal(Pig)
	PrintAnimal(Cow)
	PrintAnimal(Chicken)

	fmt.Println("Integer Test............")
	PrintAnimal(1)
	PrintAnimal(4)
}
