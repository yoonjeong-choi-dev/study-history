package main

import (
	"fmt"
	"sync"
)

// 전체 고루틴을 기다리는 작업을 하는 객체 선언
var wg sync.WaitGroup

func SumAndPrint(curProc, a, b int) {
	sum := 0
	for i := a; i <= b; i++ {
		sum += i
	}

	fmt.Printf("Cur Thread %d : Sum from %d to %d = %d\n", curProc, a, b, sum)

	// 고루틴 완료됨을 표시
	wg.Done()
}

func main() {
	from, to := 1, 1000000000
	var numWorks int = 10

	// 총 numWorks 개의 고루틴 작업 정의
	wg.Add(numWorks)

	for i := 0; i < numWorks; i++ {
		go SumAndPrint(i+1, from, to)
	}

	// 메인 고루틴은 모든 numWorks 개의 서브 루틴이 완료될 때까지 대기
	wg.Wait()
}
