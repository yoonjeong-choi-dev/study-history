package main

import (
	"log"
	pb "ordermanagement/client/order"
	"path/filepath"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials"
	"google.golang.org/grpc/credentials/oauth"

	"golang.org/x/oauth2"
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

	// grpc 통신을 위한 oauth 토큰 설정 : 실제로는 권한 서버에서 발행해줌
	tok := oauth.NewOauthAccess(fetchMockToken())

	// 서버 공개키 및 oauth 토큰을 이용한 연결 정보 설정
	opts := []grpc.DialOption{
		grpc.WithPerRPCCredentials(tok),
		// transport credentials.
		grpc.WithTransportCredentials(creds),
	}

	// set the connection with server credential & oauth
	conn, err := grpc.Dial(serverAddress, opts...)
	if err != nil {
		log.Fatalf("Cannot connect to server : %v", err)
	}
	defer conn.Close()

	// create client
	client := &Client{grpcClient: pb.NewOrderManagementClient(conn)}
	client.Main()

}

// 가짜 인증 토큰 발행
func fetchMockToken() *oauth2.Token {
	return &oauth2.Token{
		AccessToken: "yoonjeong-choi-token",
	}
}
