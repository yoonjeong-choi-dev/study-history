package main

import (
	"context"
	"log"
	pb "ordermanagement/client/order"

	"google.golang.org/grpc"
)

const (
	serverAddress = "localhost:50051"
)

func main() {
	// set the connection with intercept
	conn, err := grpc.Dial(serverAddress, grpc.WithInsecure(),
		grpc.WithUnaryInterceptor(unaryLoggingInterceptor),
		grpc.WithStreamInterceptor(streamingLogginInterceptor))
	if err != nil {
		log.Fatalf("Cannot connect to server : %v", err)
	}
	defer conn.Close()

	// create client
	client := &Client{grpcClient: pb.NewOrderManagementClient(conn)}
	client.Main()

}

/*
	인터셉터 : 메서드 실행 전후 로깅
*/
// 단일 인터셉터 구현
func unaryLoggingInterceptor(ctx context.Context, method string, req, reply interface{}, cc *grpc.ClientConn, invoker grpc.UnaryInvoker, opts ...grpc.CallOption) error {
	// Preprocessing
	log.Println(">>>>>>>>>>> [Client Interceptor] BEFORE: ", method)

	// 단순 RPC 호출을 요청하는 핸들러 호출 : 해당 메서드 요청
	err := invoker(ctx, method, req, reply, cc, opts...)

	// PostProcessing
	log.Printf(">>>>>>>>>>>[Client Interceptor] AFTER: %s\n", reply)

	return err
}

// 스트리밍 인터셉터 구현
// Step1 : 스트림을 인터셉트하기 위한 래퍼 스트림 구현
type wrappedStream struct {
	grpc.ClientStream
}

// 스트림 RPC로 전송할 메시지 스트림을 인터셉트 : 요청에 대한 전처리
func (w *wrappedStream) SendMsg(msg interface{}) error {
	log.Println(">>>>>>>>>>> [Client Stream Interceptor Wrapper] Pre-processing for Request stream")
	log.Printf(">>>>>>>>>>> [Client Stream Interceptor Wrapper] : Send a message(Type: %T)\n", msg)
	return w.ClientStream.SendMsg(msg)
}

// 스트림 RPC로 수신된 메시지 스트림을 인터셉트 : 서버 응답 스트림에 대한 후처리
func (w *wrappedStream) RecvMsg(msg interface{}) error {
	log.Println(">>>>>>>>>>> [Client Stream Interceptor Wrapper] Post-processing for Response stream")
	log.Printf(">>>>>>>>>>> [Client Stream Interceptor Wrapper] : Recieve a message(Type: %T)\n", msg)
	return w.ClientStream.RecvMsg(msg)
}

// 래퍼 스트림 팩토리 함수
func newWrappedStream(s grpc.ClientStream) grpc.ClientStream {
	return &wrappedStream{s}
}

// Step 2 : 스트리밍 인터셉터 구현 : 연결에 대한 전처리 인터셉터
func streamingLogginInterceptor(ctx context.Context, desc *grpc.StreamDesc, cc *grpc.ClientConn, method string, streamer grpc.Streamer, opts ...grpc.CallOption) (grpc.ClientStream, error) {
	// Preprocessing
	log.Println(">>>>>>>>>>> [Client Stream Interceptor] BEFORE: ", method)

	// 클라이언트 스트림 생성
	stream, err := streamer(ctx, desc, cc, method, opts...)
	if err != nil {
		log.Printf("RPC failed with error : %v\n", err)
		return nil, err
	}

	return newWrappedStream(stream), nil
}
