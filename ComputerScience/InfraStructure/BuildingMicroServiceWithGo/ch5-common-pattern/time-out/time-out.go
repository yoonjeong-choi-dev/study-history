package main

import (
	"fmt"
	"time"

	"github.com/eapache/go-resiliency/deadline"
)

func main() {

	fmt.Println("================\nNormal Request Test\n================")
	makeNormalRequest()
	fmt.Println("\n================\nTimeout Request Test\n================")
	makeTimeoutRequest()

}

func makeNormalRequest() {
	slowFunction()
}

func makeTimeoutRequest() {
	// 요청 후, 응답을 1초 기다리는 데드라인 설정
	deadLine := deadline.New(1 * time.Second)

	// 매우 느린 서비스 실행 후, 데드라인 만큼만 기다린다
	err := deadLine.Run(func(stopper <-chan struct{}) error {
		slowFunction()
		return nil
	})

	switch err {
	case deadline.ErrTimedOut:
		fmt.Println("Time Out !")
	default:
		fmt.Println(err)
	}
}

// 10초의 시간이 걸리는 매우 느린 프로세스 : 서버 프로세스에 해당
func slowFunction() {
	executeTime := 10
	for i := 0; i < executeTime; i++ {
		fmt.Println("Loop(s) :", i)
		time.Sleep(1 * time.Second)
	}
}
