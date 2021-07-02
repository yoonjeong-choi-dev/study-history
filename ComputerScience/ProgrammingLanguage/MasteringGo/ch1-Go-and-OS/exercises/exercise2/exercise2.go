package main

import (
	"fmt"
	"os"
	"strconv"
)

func main() {
	if len(os.Args) == 1 {
		fmt.Println("Please give one or more floats")
		os.Exit(1)
	}

	args := os.Args

	var sum float64 = 0
	numOfFloat := 0

	for i := 1; i < len(args); i++ {
		n, err := strconv.ParseFloat(args[i], 64)

		if err == nil {
			sum += n
			numOfFloat++
		}
	}

	if numOfFloat == 0 {
		fmt.Println("There is no number in your argument")
	} else {
		fmt.Printf("The average is %f\n", sum/float64(numOfFloat))
	}
}
