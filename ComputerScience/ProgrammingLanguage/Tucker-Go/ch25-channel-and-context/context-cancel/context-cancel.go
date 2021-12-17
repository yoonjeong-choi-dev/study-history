package main

import (
	"context"
	"fmt"
	"sync"
	"time"
)

var wg sync.WaitGroup

func PrintEverySecond(ctx context.Context) {
	tick := time.Tick(time.Second)

	for {
		select {
		// 컨텍스트 취소 발생 시 함수 종료
		case <-ctx.Done():
			fmt.Println("cotext canceled!")
			wg.Done()
			return
		case <-tick:
			fmt.Println("Tick")
		}
	}
}

func main() {
	wg.Add(1)

	// 5초 뒤 취소 : 5초뒤 자동으로 cancel 호출
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	go PrintEverySecond(ctx)

	wg.Wait()
}
