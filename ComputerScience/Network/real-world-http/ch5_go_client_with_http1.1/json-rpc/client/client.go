package main

import (
	"log"
	"net/rpc/jsonrpc"
)

type Args struct {
	A, B int
}

func main() {
	// json-rpc 호출을 위한 클라이언트 소켓 생성
	client, err := jsonrpc.Dial("tcp", "localhost:18888")
	if err != nil {
		panic(err)
	}

	// rpc 호출에 넘길 인자 구조체 생성
	args := &Args{4, 5}

	// rpc 결과를 저장할 변수
	var result int

	// rpc 호출 및 결과 출력
	err = client.Call("Calculator.Multiply", args, &result)
	if err != nil {
		panic(err)
	}
	log.Printf("4 * 5 = %d\n", result)
}
