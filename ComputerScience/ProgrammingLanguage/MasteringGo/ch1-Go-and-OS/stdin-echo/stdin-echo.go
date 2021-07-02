package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	f := os.Stdin
	defer f.Close()

	// 파일 입출력 기능인 bufio.NewScanner에 표준 입력 등록
	scanner := bufio.NewScanner(f)

	// 입력 값을 읽어 그대로 출력
	fmt.Println("Press 'END'' to end this program")

	for scanner.Scan() {
		fmt.Println(">", scanner.Text())
	}
}
