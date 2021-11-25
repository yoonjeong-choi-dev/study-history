package main

import (
	"log"
	pb "ordermanagement/client/order"
	"path/filepath"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials"
)

var (
	serverAddress = "localhost:50051"
	hostname      = "localhost"

	// 단뱡향 연결에서는 서버의 자체 인증 공개키가 필요
	// 베이직 인증의 헤더를 암호화 하기 위해 필요
	crtFile = filepath.Join("..", "..", "certs", "server.crt")
)

// 클라이언트의 경우 common-name 관련 이슈로, GODEBUG=x509ignoreCN=0 go run *.go 로 돌려야함
func main() {
	// 서버 공개키를 이용하여 클라이언트 인증서 생성
	creds, err := credentials.NewClientTLSFromFile(crtFile, hostname)
	if err != nil {
		log.Fatalf("Fail to load credentail : %v", err)
	}

	// 헤더에 포함시킬 커스텀 자격 증명 생성
	auth := BasicAuth{
		username: "admin",
		password: "admin",
	}

	// 단방향 TLS 및 베이진 인증 설정
	opts := []grpc.DialOption{
		grpc.WithTransportCredentials(creds),
		grpc.WithPerRPCCredentials(auth),
	}

	// set the connection with server credentail
	conn, err := grpc.Dial(serverAddress, opts...)
	if err != nil {
		log.Fatalf("Cannot connect to server : %v", err)
	}
	defer conn.Close()

	// create client
	client := &Client{grpcClient: pb.NewOrderManagementClient(conn)}
	client.Main()

}
