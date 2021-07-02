package main

import (
	"fmt"
	"runtime"
	"time"
)

func printGCInfo(mem runtime.MemStats) {
	// GC 통계에 대한 최신 정보 조회 및 출력
	runtime.ReadMemStats(&mem)

	fmt.Println("mem.Alloc : ", mem.Alloc)
	fmt.Println("mem.TotalAlloc : ", mem.TotalAlloc)
	fmt.Println("mem.HeapAlloc : ", mem.HeapAlloc)
	fmt.Println("mem.NumGC : ", mem.NumGC)
	fmt.Println("--------------------------------------")
}

func main() {
	var mem runtime.MemStats
	printGCInfo(mem)

	// Test 1 : 대용량의 슬라이스 생성 => 방대한 메모리 할당으로 인해 GC 발생
	for i := 0; i < 10; i++ {
		s := make([]byte, 50000000)
		if s == nil {
			fmt.Println("Operation failed")
		}
	}
	printGCInfo(mem)

	// Test 2 : 더 많은 용량의 슬라이스 생성
	// sleep을 통해 GODEBUG=gctrace=1의 출력정보를 천천히 확인 가능
	for i := 0; i < 10; i++ {
		s := make([]byte, 100000000)
		if s == nil {
			fmt.Println("Operation failed")
		}
		time.Sleep(5 * time.Second)
	}
	printGCInfo(mem)
}
