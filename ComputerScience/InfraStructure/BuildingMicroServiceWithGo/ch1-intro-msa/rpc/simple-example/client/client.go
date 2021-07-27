package client

import (
	"fmt"
	"log"
	"net/rpc"

	"building_msa_with_go/ch1/rpc/simple-example/contract"
)

const PORT_NUMBER = 1234

// RPC 통신을 위한 클라이언트 객체 생성
func CreateClient() *rpc.Client {
	client, err := rpc.Dial("tpc", fmt.Sprintf("localhost:%v", PORT_NUMBER))
	if err != nil {
		log.Fatal("dialing:", err)
	}

	return client
}

// 클라이언트 객체에서 RPC 메서드 호출
func PerformRequest(client *rpc.Client) contract.HelloWorldResponse {
	// 요청에 사용할 파라미터 객체 생성
	args := &contract.HelloWorldRequest{Name: "World"}

	// 응답 객체 생성
	var reply contract.HelloWorldResponse

	// RPC 호출(Call)
	err := client.Call("HelloWorldHandler.HelloWorld", args, &reply)
	if err != nil {
		log.Fatal("error:", err)
	}

	return reply
}
