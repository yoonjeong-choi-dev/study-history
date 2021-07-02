package main

import (
	"io"
	"os"
)

func main() {
	myString := ""
	args := os.Args

	if len(args) == 1 {
		myString = "Please give me one argument!"
	} else {
		myString = args[1]
	}

	io.WriteString(os.Stdout, "This is Standard output. From now on, Standard Error\n")
	io.WriteString(os.Stderr, myString)
	io.WriteString(os.Stderr, "\n")
}
