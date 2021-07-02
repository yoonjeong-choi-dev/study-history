package main

import "runtime"

type data struct {
	i, j int
}

func main() {
	var largeNum = 40000000
	var slices []data

	// 대용량 메모리의 슬라이스 생성
	for i := 0; i < largeNum; i++ {
		value := int(i)
		slices = append(slices, data{value, value})
	}
	runtime.GC()

	// GC가 빠르게 작동하지 않게 만든다
	_ = slices[0]
}
