package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var a, b int

	// 표준 입력 스트림을 읽어오는 Reader 객체 생성
	// 인수로 입력되는 입력 스트림을 가지고 Reader 객체 생성
	stdin := bufio.NewReader(os.Stdin)

	for {
		// 표준 입력 스트림에 저장할 두 개의 정수 입력
		fmt.Print("정수 2개 입력 :")
		_, err := fmt.Scanln(&a, &b)

		if err != nil {
			// 입력 에러 발생 시, 에러 출력 후 스트림 지우기
			fmt.Println(err)
			stdin.ReadString('\n')
		} else {
			// 제대로 입력 한 경우 끝.
			fmt.Println("Your input :", a, b)
			break
		}
	}

}
