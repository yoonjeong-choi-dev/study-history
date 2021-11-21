package main

import (
	"context"
	"log"
	"net"
	pb "ordermanagement/service/order"

	"google.golang.org/grpc"
)

const (
	port = ":50051"
)

func main() {
	// 서비스 초기화
	orderManager := &service{OrderBatchSize: 3}
	orderManager.Init()
	orderManager.GenerateSampleData()

	// TCP 리스너
	listener, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalf("Failed to listen: %v", err)
	}

	// grpc 서비스 등록 with intercepter
	s := grpc.NewServer(
		grpc.UnaryInterceptor(unaryLoggingInterceptor),
		grpc.StreamInterceptor(streamingLogginInterceptor))
	pb.RegisterOrderManagementServer(s, orderManager)

	log.Printf("Starting gRPC listener on port " + port)
	if err := s.Serve(listener); err != nil {
		log.Fatalf("Fail to start : %v", err)
	}
}

/*
	인터셉터 : 메서드 실행 전후 로깅
*/
// 단일 인터셉터 구현
func unaryLoggingInterceptor(ctx context.Context, req interface{}, info *grpc.UnaryServerInfo, handler grpc.UnaryHandler) (interface{}, error) {
	// Preprocessing
	log.Println(">>>>>>>>>>> [Server Interceptor] BEFORE: ", info.FullMethod)

	// 단순 RPC 실행을 완료하는 핸들러 호출 : 해당 메서드 호출
	m, err := handler(ctx, req)

	// PostProcessing
	log.Printf(">>>>>>>>>>>[Server Interceptor] AFTER: %s\n", m)

	return m, err
}

// 스트리밍 인터셉터 구현
// Step1 : 스트림을 인터셉트하기 위한 래퍼 스트림 구현
type wrappedStream struct {
	grpc.ServerStream
}

// 스트림 RPC로 수신된 메시지 스트림을 인터셉트 : 클라이언트 스트림에 대한 전처리
func (w *wrappedStream) RecvMsg(msg interface{}) error {
	log.Println(">>>>>>>>>>> [Server Stream Interceptor Wrapper] Pre-processing for Request stream")
	log.Printf(">>>>>>>>>>> [Server Stream Interceptor Wrapper] : Recieve a message(Type: %T)\n", msg)
	return w.ServerStream.RecvMsg(msg)
}

// 스트림 RPC로 전송할 메시지 스트림을 인터셉트 : 응답에 대한 후처리
func (w *wrappedStream) SendMsg(msg interface{}) error {
	log.Println(">>>>>>>>>>> [Server Stream Interceptor Wrapper] Post-processing for Response stream")
	log.Printf(">>>>>>>>>>> [Server Stream Interceptor Wrapper] : Send a message(Type: %T)\n", msg)
	return w.ServerStream.SendMsg(msg)
}

// 래퍼 스트림 팩토리 함수
func newWrappedStream(s grpc.ServerStream) grpc.ServerStream {
	return &wrappedStream{s}
}

// Step 2 : 스트리밍 인터셉터 구현 : 연결에 대한 인터셉터 => 연결 시작/끝에서 로직 처리
func streamingLogginInterceptor(srv interface{}, ss grpc.ServerStream, info *grpc.StreamServerInfo, handler grpc.StreamHandler) error {
	// Preprocessing
	log.Println(">>>>>>>>>>> [Server Stream Interceptor] BEFORE: ", info.FullMethod)

	// 스트리밍 RPC 실행을 완료하는 핸들러 호출 : 해당 메서드 호출
	err := handler(srv, newWrappedStream(ss))
	if err != nil {
		log.Printf("RPC failed with error : %v\n", err)
	} else {
		// Postprocessing
		log.Printf(">>>>>>>>>>> [Server Stream Interceptor] AFTER: EOF\n\n")
	}

	return err
}
