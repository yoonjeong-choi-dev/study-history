package main

import (
	"errors"
	"fmt"
)

func compareError(a, b int) error {
	if a == b {
		return nil
	} else {
		err := errors.New("Two integers are not equal")
		return err
	}
}

func main() {
	err := compareError(1, 1)
	if err == nil {
		fmt.Println("compareError() ended normally")
	} else {
		fmt.Println(err)
	}

	err = compareError(1, 2)
	if err == nil {
		fmt.Println("compareError() ended normally")
	} else {
		fmt.Println("Error message is.... by calling 'err.Error()'")
		fmt.Println(err.Error())
	}
}
