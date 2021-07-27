package server

import (
	"fmt"
	"log"
	"net"
	"net/rpc"

	"building_msa_with_go/ch1/rpc/simple-example/contract"
)

const PORT_NUMBER = 1234

// RPC 용 서버 프로시져 정의
type HelloWorldHandler struct{}

func (h *HelloWorldHandler) HelloWorld(args *contract.HelloWorldRequest, reply *contract.HelloWorldResponse) error {
	reply.Message = "Hello " + args.Name
	return nil
}

// 서버에서 제공할 프로시저 공개 메드
func StartServer() {
	// 프로시저를 위한 객체 생성 및 RPC 등록
	helloWorld := &HelloWorldHandler{}
	rpc.Register(helloWorld)

	// RPC를 위한 프로토콜을 이용하여 소켓 생성 및 IP/포트에 바인딩
	l, err := net.Listen("tcp", fmt.Sprintf(":%v", PORT_NUMBER))
	if err != nil {
		log.Fatal(fmt.Sprintf("Unable to listen on given port: %s", err))
	}
	defer l.Close() // 서버 종료시, 소켓 해제

	// 무한 루프를 통해 연결이 발생하는지 확인
	for {
		// 연결이 이루어질 때까지 블로킹 상태
		conn, _ := l.Accept()

		// 연결이 되면 클라이언트의 처리가 완료될 때까지 대기
		// 고루틴을 사용하여, 클라이언트의 처리가 완료되는 것을 기다리지 않고 다른 클라이언트의 연결을 위해 대기 상태
		go rpc.ServeConn(conn)
	}
}
