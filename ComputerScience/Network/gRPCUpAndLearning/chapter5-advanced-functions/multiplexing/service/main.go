package main

import (
	"log"
	"net"
	pb "ordermanagement/service/order"

	"google.golang.org/grpc"
	hello_pb "google.golang.org/grpc/examples/helloworld/helloworld"
)

const (
	port = ":50051"
)

func main() {
	// 서비스1 초기화
	orderManager := &service{OrderBatchSize: 3}
	orderManager.Init()
	orderManager.GenerateSampleData()

	// TCP 리스너
	listener, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalf("Failed to listen: %v", err)
	}

	// 서버 생성
	s := grpc.NewServer()

	// grpc 서비스1 등록
	pb.RegisterOrderManagementServer(s, orderManager)

	// grpc 서비스2 등록
	hello_pb.RegisterGreeterServer(s, &helloService{})

	log.Printf("Starting gRPC listener on port " + port)
	if err := s.Serve(listener); err != nil {
		log.Fatalf("Fail to start : %v", err)
	}
}
