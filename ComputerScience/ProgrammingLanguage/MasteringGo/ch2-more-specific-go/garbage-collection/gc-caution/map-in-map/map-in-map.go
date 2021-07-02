package main

import "runtime"

func main() {
	var largeNum = 40000000

	// 맵에 대한 맵 생성
	largeMap := make([]map[int]int, 200)
	for i := range largeMap {
		largeMap[i] = make(map[int]int)
	}

	// largeMap의 각 맵에 데이터 할당
	for i := 0; i < largeNum; i++ {
		value := int(i)
		largeMap[i%200][value] = value
	}
	runtime.GC()

	// GC가 빠르게 작동하지 않게 만든다
	_ = largeMap[0][0]
}
