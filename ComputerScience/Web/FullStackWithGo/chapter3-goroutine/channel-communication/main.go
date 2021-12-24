package main

import (
	"fmt"
	"time"
)

func sender(n int, ch chan int) {
	for i := 0; i < 10; i++ {
		ch <- i
	}

	// 다른 고루틴에게 채널이 닫혔음을 알린다
	close(ch)
}

func recieverFor(ch chan int) {
	// 해당 채널에 데이터가 들어올 때까지 대기
	for {
		// ok : 채널이 닫혔는지 여부 확인
		chanData, ok := <-ch
		if !ok {
			fmt.Println("recieverFor : This channel is closed...")
			break
		}

		fmt.Println("recieverFor : Receive the data from the channel :", chanData)
	}
}

func recieverRange(ch chan int) {
	// 해당 채널에 데이터가 들어올 때까지 대기
	for chanData := range ch {
		fmt.Println("recieverRange : Receive the data from the channel :", chanData)
	}
}

func main() {
	myChannel := make(chan int)
	go sender(10, myChannel)
	go recieverRange(myChannel)
	go recieverFor(myChannel)

	time.Sleep(time.Second)
}
