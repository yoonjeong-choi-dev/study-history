package main

import (
	"fmt"
	"os"
	"strconv"
)

func checkErr(err error) {
	if err != nil {
		panic(err)
	}
}

func main() {
	if len(os.Args) == 1 {
		fmt.Println("Please give one or more floats")
		os.Exit(1)
	}

	args := os.Args
	min, err := strconv.ParseFloat(args[1], 64)
	checkErr(err)

	max, err := strconv.ParseFloat(args[1], 64)
	checkErr(err)

	for i := 2; i < len(args); i++ {
		n, err := strconv.ParseFloat(args[i], 64)
		checkErr(err)

		if n < min {
			min = n
		}

		if n > max {
			max = n
		}
	}

	fmt.Println("Min : ", min)
	fmt.Println("Max : ", max)
}
