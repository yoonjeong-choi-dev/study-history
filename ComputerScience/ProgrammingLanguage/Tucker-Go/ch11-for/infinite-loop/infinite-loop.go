package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	stdin := bufio.NewReader(os.Stdin)
	fmt.Println("짝수 입력받을 때까지 무한 입력!!!!")

	var number int
	for {
		fmt.Print("입력 : ")
		_, err := fmt.Scanln(&number)
		if err != nil {
			fmt.Println("숫자를 입력하세요.")

			// 표준입력버퍼 flush
			stdin.ReadString('\n')
			continue
		}

		fmt.Printf("입력한 숫자는 %d입니다\n", number)
		if number%2 == 0 {
			fmt.Println("입력한 숫자는 짝수입니다. 반복문 종료!")
			break
		}
	}
}
