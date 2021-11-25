package main

import (
	"crypto/tls"
	"crypto/x509"
	"io/ioutil"
	"log"
	pb "ordermanagement/client/order"
	"path/filepath"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials"
)

var (
	serverAddress = "localhost:50051"
	hostname      = "localhost"

	// 클라이언트의 비밀키 및 서명 파일 path
	crtFile = filepath.Join("..", "..", "certs", "client.crt")
	keyFile = filepath.Join("..", "..", "certs", "client.key")

	// ca 인증서 파일 path
	caFile = filepath.Join("..", "..", "certs", "ca.crt")
)

// GODEBUG=x509ignoreCN=0 go run *.go 로 실행 필요
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

	// gprc 클라이언트 옵션 : 모든 요청 연결에 대해 TLS 활성화
	// 등록된 CA 서명 인증서를 이용하여 클라이언트 인증서 검증
	opts := []grpc.DialOption{
		grpc.WithTransportCredentials(credentials.NewTLS(&tls.Config{
			ServerName:   hostname, // 인증서의 Common Name
			Certificates: []tls.Certificate{cert},
			RootCAs:      certPool,
		})),
	}

	// set the connection with server with credential options
	conn, err := grpc.Dial(serverAddress, opts...)
	if err != nil {
		log.Fatalf("Cannot connect to server : %v", err)
	}
	defer conn.Close()

	// create client
	client := &Client{grpcClient: pb.NewOrderManagementClient(conn)}
	client.Main()

}
