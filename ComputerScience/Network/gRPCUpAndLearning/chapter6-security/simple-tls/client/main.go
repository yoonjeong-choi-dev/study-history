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
	crtFile = filepath.Join("..", "..", "certs", "server.crt")
)

// 클라이언트의 경우 common-name 관련 이슈로, GODEBUG=x509ignoreCN=0 go run *.go 로 돌려야함
func main() {
	// 서버 공개키를 이용하여 클라이언트 인증서 생성
	creds, err := credentials.NewClientTLSFromFile(crtFile, hostname)
	if err != nil {
		log.Fatalf("Fail to load credentail : %v", err)
	}

	// set the connection with server credentail
	conn, err := grpc.Dial(serverAddress, grpc.WithTransportCredentials(creds))
	if err != nil {
		log.Fatalf("Cannot connect to server : %v", err)
	}
	defer conn.Close()

	// create client
	client := &Client{grpcClient: pb.NewOrderManagementClient(conn)}
	client.Main()

}
