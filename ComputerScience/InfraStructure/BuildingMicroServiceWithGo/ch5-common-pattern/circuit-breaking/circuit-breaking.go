package main

import (
	"fmt"
	"time"

	"github.com/eapache/go-resiliency/breaker"
)

func main() {
	errorThreshold := 3   // 회로가 차단(열린 상태)되는 에러 발생 임계치
	successThreshold := 1 // 반개방 상태의 회로가 닫힌 상태가 되는 성공 횟수 임계치
	circuitBreaker := breaker.New(errorThreshold, successThreshold, 5*time.Second)

	for {
		result := circuitBreaker.Run(func() error {
			// Call a service with error
			fmt.Print("Service Call Start.... : ")
			time.Sleep(2 * time.Second)
			return fmt.Errorf("TimeoutFailed")
		})

		switch result {
		case nil:
			// success
		case breaker.ErrBreakerOpen:
			// 회로 차단 open : 서비스 호출이 실행되지 않음
			fmt.Println("Circuit Breaker Open : 실패")
		default:
			fmt.Println(result)
		}

		time.Sleep(500 * time.Millisecond)
	}
}
