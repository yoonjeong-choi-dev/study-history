package main

import (
	"log"
	"net"
	"net/http"
	"net/rpc"
	"net/rpc/jsonrpc"
)

/*
RPC 구현을 위해 정의해야 하는 목록
1. 호출할 메서드가 속한 구조체(public)
2. 호출할 메서드(public)
3. 호출할 메서드에 넘길 인수 구조체(public)
*/

// rpc 메서드가 속한 구조체 정의
type Calculator int

// RPC로 외부에서 호출할 메서드 정의
func (c *Calculator) Multiply(args Args, result *int) error {
	log.Printf("Multiply called : %d, %d\n", args.A, args.B)
	*result = args.A * args.B
	return nil
}

// 외부에서 호출될 인수 구조체 정의
type Args struct {
	A, B int
}

func main() {
	calculator := new(Calculator)

	// RPC용 서버 생성 및 메서드가 구현된 구조체 등록
	server := rpc.NewServer()
	server.Register((calculator))

	// 서버 open
	http.Handle(rpc.DefaultDebugPath, server)
	log.Println("Start http listening : 18888")
	listener, err := net.Listen("tcp", ":18888")
	if err != nil {
		panic(err)
	}

	for {
		connect, err := listener.Accept()
		if err != nil {
			panic(err)
		}
		// 클라이언트 접속시, json-rpc 코덱을 만들어 서버 등록(고루틴)
		go server.ServeCodec(jsonrpc.NewServerCodec(connect))
	}
}
