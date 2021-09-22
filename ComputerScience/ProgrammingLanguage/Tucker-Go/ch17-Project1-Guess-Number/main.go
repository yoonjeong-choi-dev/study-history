package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"time"
)

// 표준 입력 스트림
var stdin = bufio.NewReader(os.Stdin)

// 숫자 입력 관련 함수
func InputIntValue() (int, error) {
	var number int

	// 숫자 입력
	_, err := fmt.Scanln(&number)
	if err != nil {
		// 에러 발생 시, 입력 스트림을 비운다
		// 에러 발생 이유 1 : 숫자가 아님
		stdin.ReadString('\n')
	}

	return number, err
}

func main() {
	// 랜덤 숫자 생성 : 현 시간을 seed로 유사 난수 생성
	rand.Seed(time.Now().UnixNano())
	target := rand.Intn(100)

	tryCount := 1

	fmt.Println("===============================================")
	fmt.Println("숫자 게임 시작 !!!!!")
	for {
		fmt.Printf("숫자값을 입력하세요 : ")
		number, err := InputIntValue()
		if err != nil {
			fmt.Println("숫자만 입력하세요!")
		} else {
			if number == target {
				fmt.Printf("축하합니다! %d 횟수만에 맞췄습니다!\n", tryCount)
				break
			} else {
				tryCount++
				if number > target {
					fmt.Printf("입력하신 숫자가 %d보다 작습니다\n", number)
				} else {
					fmt.Printf("입력하신 숫자가 %d보다 큽니다\n", number)
				}
			}
		}
	}

	fmt.Println("===============================================")
}
