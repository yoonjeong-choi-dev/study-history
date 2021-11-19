package main

import (
	"log"
	"net"

	pb "productinfo/service/ecommerce"

	"google.golang.org/grpc"
)

const (
	port = ":50051"
)

func main() {
	// 서버와 바인딩할 TCP 리스너 생성
	listener, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalf("Failed to listen: %v", err)
	}

	// grpc를 구동할 서버 생성 및 구현된 서비스 등록
	s := grpc.NewServer()
	pb.RegisterProductInfoServer(s, &prodService{})

	log.Printf("Starting gRPC listener on port " + port)
	if err := s.Serve(listener); err != nil {
		log.Fatalf("Fail to serve : %v", err)
	}
}
