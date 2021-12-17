package main

import (
	"fmt"
	"sync"
	"time"
)

func square(wg *sync.WaitGroup, ch chan int) {

	// 채널에 데이터가 들어올 때까지 대기
	for n := range ch {
		fmt.Printf("Square: %d\n", n*n)
		time.Sleep(time.Second)
	}

	wg.Done()
}

func main() {
	var wg sync.WaitGroup
	ch := make(chan int, 5)

	wg.Add(1)
	go square(&wg, ch)

	for i := 0; i < 10; i++ {
		ch <- i * 2
	}

	// 채널에 데이터를 모두 넣고 완료됨을 표시
	// => 채널에서 데이터가 들어오기를 대기하는 쪽에 알리는 역할
	close(ch)

	wg.Wait()
}
