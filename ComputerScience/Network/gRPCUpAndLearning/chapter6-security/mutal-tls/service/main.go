package main

import (
	"crypto/tls"
	"crypto/x509"
	"io/ioutil"
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

	// ca 인증서 파일 path
	caFile = filepath.Join("..", "..", "certs", "ca.crt")
)

func main() {
	// 인증서 관련 파일 로드 및 인증서 생성
	cert, err := tls.LoadX509KeyPair(crtFile, keyFile)
	if err != nil {
		log.Fatalf("Fail to load key pair : %v", err)
	}

	// ca 인증서 로드
	ca, err := ioutil.ReadFile(caFile)
	if err != nil {
		log.Fatalf("Fail to load CA certificate : %s", err)
	}

	// 인증서 풀 생성 및 ca 인증서 등록
	certPool := x509.NewCertPool()
	if ok := certPool.AppendCertsFromPEM(ca); !ok {
		log.Fatal("Fail to append ca certificate")
	}

	// gprc 서버 옵션 : 모든 요청 연결에 대해 TLS 활성화
	// 등록된 CA 서명 인증서를 이용하여 클라이언트 인증서 검증
	opts := []grpc.ServerOption{
		grpc.Creds(credentials.NewTLS(&tls.Config{
			ClientAuth:   tls.RequireAndVerifyClientCert,
			Certificates: []tls.Certificate{cert},
			ClientCAs:    certPool,
		})),
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
