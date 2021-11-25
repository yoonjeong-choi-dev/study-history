package main

import (
	"crypto/tls"
	"log"
	"net"
	pb "ordermanagement/service/order"
	"path/filepath"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials"
)

var (
	port = ":50051"

	// 비밀키 및 서명 파일 path
	crtFile = filepath.Join("..", "..", "certs", "server.crt")
	keyFile = filepath.Join("..", "..", "certs", "server.key")
)

func main() {
	// 인증서 관련 파일 로드 및 인증서 생성
	cert, err := tls.LoadX509KeyPair(crtFile, keyFile)
	if err != nil {
		log.Fatalf("Fail to load key pair : %v", err)
	}

	// gprc 서버 옵션
	opts := []grpc.ServerOption{
		grpc.Creds(credentials.NewServerTLSFromCert(&cert)),
	}

	// 서비스 초기화
	orderManager := &service{OrderBatchSize: 3}
	orderManager.Init()
	orderManager.GenerateSampleData()

	// grpc 서비스 등록 with tls options
	s := grpc.NewServer(opts...)
	pb.RegisterOrderManagementServer(s, orderManager)

	// TCP 리스너
	listener, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalf("Failed to listen: %v", err)
	}

	log.Printf("Starting gRPC listener on port " + port)
	if err := s.Serve(listener); err != nil {
		log.Fatalf("Fail to start : %v", err)
	}
}
