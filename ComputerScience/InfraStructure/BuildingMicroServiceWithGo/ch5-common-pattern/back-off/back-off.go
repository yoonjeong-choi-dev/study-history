package main

import (
	"fmt"
	"time"

	"github.com/eapache/go-resiliency/retrier"
)

func main() {
	// 최대 3번까지 1초 간격으로 요청 재시도
	maxBackoffNumbers := 3
	backOff := retrier.New(retrier.ConstantBackoff(maxBackoffNumbers, 1*time.Second), nil)

	attemptCount := 0
	err := backOff.Run(func() error {
		fmt.Println("Attempt :", attemptCount)
		attemptCount++
		return fmt.Errorf("Failed")
	})

	if err != nil {
		fmt.Println("Error :", err)
	}
}
