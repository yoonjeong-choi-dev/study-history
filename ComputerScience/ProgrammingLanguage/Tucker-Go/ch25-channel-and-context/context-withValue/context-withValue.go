package main

import (
	"context"
	"fmt"
	"sync"
)

var wg sync.WaitGroup

func square(ctx context.Context) {
	// 컨텍스트에서 값 읽기
	if v := ctx.Value("number"); v != nil {
		// v는 interface{} 형태 => int 형 변환
		n := v.(int)
		fmt.Printf("pow(%d, 2) = %d\n", n, n*n)
	}
	wg.Done()
}

func main() {
	wg.Add(10)

	for i := 0; i < 10; i++ {
		ctx := context.WithValue(context.Background(), "number", i+1)
		go square(ctx)
	}
	wg.Wait()
}
