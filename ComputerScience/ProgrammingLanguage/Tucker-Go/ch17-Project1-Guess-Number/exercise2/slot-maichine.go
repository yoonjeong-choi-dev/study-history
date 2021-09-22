package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"time"
)

const (
	Balance       = 1000
	EarnPoint     = 500
	LosePoint     = 100
	VictoryPoint  = 5000
	GameoverPoint = 0
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
	// 랜덤 숫자 생성기 : 현 시간을 seed로 유사 난수 생성
	rand.Seed(time.Now().UnixNano())

	mybalance := Balance

	fmt.Println("===============================================")
	fmt.Println("슬롯머신 시작!!!!")
	for {
		fmt.Print("1~5 사이 숫자를 입력하세요 : ")
		slot, err := InputIntValue()

		if err != nil {
			fmt.Println("숫자만 입력하세요!")
		} else if slot < 1 || slot > 5 {
			fmt.Println("1~5 사이의 숫자만 입력하세요!!")
		} else {
			target := rand.Intn(5) + 1
			if slot == target {
				mybalance += EarnPoint
				fmt.Println("당첨!!. 현재 잔액 : ", mybalance)

				if mybalance >= VictoryPoint {
					fmt.Println("승리하였습니다!")
					break
				}
			} else {
				mybalance -= LosePoint
				fmt.Println("실패...! 현재 잔액 : ", mybalance)

				if mybalance <= GameoverPoint {
					fmt.Println("게임 오버 ㅠㅠ")
					break
				}
			}

		}

	}

	fmt.Println("===============================================")
}
