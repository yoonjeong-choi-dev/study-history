package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"net/http"
	"net/rpc"
	"net/rpc/jsonrpc"

	"building_msa_with_go/ch1/rpc/simple-example/contract"
)

const PORT_NUMBER = 1234

func main() {
	StartServer()
}

// RPC 용 서버 프로시져 정의
type HelloWorldHandler struct{}

func (h *HelloWorldHandler) HelloWorld(args *contract.HelloWorldRequest, reply *contract.HelloWorldResponse) error {
	reply.Message = "You said.. " + args.Name
	log.Println(reply.Message)
	return nil
}

// NewServerCodec에 넘길 ReadWriteCloser 인터페이스 구현체
// 해당 구현체를 이용하여 요청을 읽고 응답에 써서 클라이언트에 전송
type HttpConn struct {
	in  io.Reader
	out io.Writer
}

func (c *HttpConn) Read(p []byte) (n int, err error)  { return c.in.Read(p) }
func (c *HttpConn) Write(d []byte) (n int, err error) { return c.out.Write(d) }
func (c *HttpConn) Close() error                      { return nil }

// RPC 용 핸들러
func httpHandlerForRPC(w http.ResponseWriter, r *http.Request) {
	// RPC 요청 읽기 및 응답 작성을 위한 서버 코덱 생성 및 요청 처리
	serveCodec := jsonrpc.NewServerCodec(&HttpConn{in: r.Body, out: w})
	err := rpc.ServeRequest(serveCodec)
	if err != nil {
		log.Printf("Error whilte serving JSON reqeust: %v", err)
		http.Error(w, "Error whilte serving JSON reqeust, details have been logged.", 500)
		return
	}
}

// 서버에서 제공할 프로시저 공개 메드
func StartServer() {
	// 프로시저를 위한 객체 생성 및 RPC 등록
	helloWorld := new(HelloWorldHandler)
	rpc.Register(helloWorld)

	// RPC를 위한 프로토콜을 이용하여 소켓 생성 및 IP/포트에 바인딩
	listener, err := net.Listen("tcp", fmt.Sprintf(":%v", PORT_NUMBER))
	if err != nil {
		log.Fatal(fmt.Sprintf("Unable to listen on given port: %s", err))
	}

	// http 서버를 시작하면서, RPC용 핸들러 전달
	http.Serve(listener, http.HandlerFunc(httpHandlerForRPC))
}
