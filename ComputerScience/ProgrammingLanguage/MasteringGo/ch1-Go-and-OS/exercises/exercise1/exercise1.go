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
	isCotainedNumber := false

	for i := 1; i < len(args); i++ {
		n, err := strconv.ParseFloat(args[i], 64)

		if err == nil {
			sum += n
			isCotainedNumber = true
		}
	}

	if isCotainedNumber {
		fmt.Printf("The sum is %f\n", sum)
	} else {
		fmt.Println("There is no number in your argument")
	}
}
