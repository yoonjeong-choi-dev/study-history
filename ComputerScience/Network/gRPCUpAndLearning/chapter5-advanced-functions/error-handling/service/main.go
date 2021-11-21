package main

import (
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

	// grpc 서비스 등록
	s := grpc.NewServer()
	pb.RegisterOrderManagementServer(s, orderManager)

	log.Printf("Starting gRPC listener on port " + port)
	if err := s.Serve(listener); err != nil {
		log.Fatalf("Fail to start : %v", err)
	}
}
