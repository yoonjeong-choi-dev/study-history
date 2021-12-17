package main

import (
	"fmt"
	"sync"
	"time"
)

type Car struct {
	Body  string
	Tire  string
	Color string
}

var wg sync.WaitGroup
var startTime = time.Now()

func MakeBody(tireCh chan *Car) {
	// 1초마다 하나씩 생성
	tick := time.Tick(time.Second)

	// 총 10개(10초/1초) 자동차 생성
	after := time.After(10 * time.Second)

	for {
		select {
		case <-tick:
			// 몸체 만들기
			car := &Car{}
			car.Body = "Sports Car"

			// 몸체 만든 후 바퀴 생산 영역으로 전달
			tireCh <- car
		case <-after:
			close(tireCh)
			wg.Done()
			return
		}
	}
}

func InstallTire(tireCh, paintCh chan *Car) {
	// 몸체가 만들어 질때 까지 대기
	for car := range tireCh {
		// 바퀴 생성
		time.Sleep(time.Second)
		car.Tire = "Winter Tire"

		// 바퀴 생성 후 페인트 영역으로 전달
		paintCh <- car
	}

	wg.Done()
	close(paintCh)
}

func PaintCar(paintCh chan *Car) {
	// 바퀴가 생산 될때 까지 대기
	for car := range paintCh {
		time.Sleep(time.Second)
		car.Color = "Red"

		// 생산 완료 출력
		duration := time.Now().Sub(startTime)
		fmt.Printf("[%.2f(s)] Completed Car: %s %s %s\n", duration.Seconds(), car.Body, car.Tire, car.Color)
	}
	wg.Done()
}

func main() {
	// 생산 영역(생산자-소비자) 사이를 연결하는 채널 생성
	tireCh := make(chan *Car)
	paintCh := make(chan *Car)

	fmt.Println("Start Factory\n")

	wg.Add(3)

	go MakeBody(tireCh)
	go InstallTire(tireCh, paintCh)
	go PaintCar(paintCh)

	wg.Wait()
	fmt.Println("Close the factory")
}
