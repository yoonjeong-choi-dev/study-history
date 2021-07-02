package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	//var f *os.File
	f := os.Stdin
	defer f.Close() // 프로그램 종료 시 파일 리소스 반납

	// 파일 입출력 기능인 bufio.NewScanner에 표준 입력 등록
	scanner := bufio.NewScanner(f)

	fmt.Println("Press 'END' to end this program")

	fmt.Print("Input : ")
	for scanner.Scan() {
		inputText := scanner.Text()
		if inputText == "END" {
			break
		}

		n, err := strconv.ParseInt(inputText, 0, 64)
		if err != nil {
			fmt.Println("[WARN] Please enter an integer!!")
		} else {
			fmt.Printf("Your integer is %d\n", n)

		}
		fmt.Print("Input : ")
	}
}
