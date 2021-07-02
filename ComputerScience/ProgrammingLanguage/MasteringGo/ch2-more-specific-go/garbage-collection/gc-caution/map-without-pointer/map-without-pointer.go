package main

import "runtime"

func main() {
	var largeNum = 40000000
	largeMap := make(map[int]int)

	// 대용량 메모리의 맵(값 저장) 생성
	for i := 0; i < largeNum; i++ {
		value := int(i)
		largeMap[value] = value
	}
	runtime.GC()

	// GC가 빠르게 작동하지 않게 만든다
	_ = largeMap[0]
}
