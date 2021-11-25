package main

import (
	"context"
	"crypto/tls"
	"log"
	"net"
	pb "ordermanagement/service/order"
	"path/filepath"
	"strings"

	"google.golang.org/grpc"
	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/credentials"
	"google.golang.org/grpc/metadata"
	"google.golang.org/grpc/status"
)

var (
	port = ":50051"

	// 인증 관련 에러 정의
	errMissingMetadata = status.Errorf(codes.InvalidArgument, "missing metadata")
	errInvalidToken    = status.Errorf(codes.Unauthenticated, "invalid credentials")

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
		grpc.UnaryInterceptor(unaryAuthCheck),
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

// oauth 토큰 검사를 위한 인터셉터 구현
func validateAuth(auth []string) bool {
	if len(auth) < 1 {
		return false
	}

	// 문자열 추출 및 oauth 토큰 정보 확인
	token := strings.TrimPrefix(auth[0], "Bearer ")
	return token == "yoonjeong-choi-token"
}

func unaryAuthCheck(ctx context.Context, req interface{}, info *grpc.UnaryServerInfo, handler grpc.UnaryHandler) (interface{}, error) {
	// Preprocessing : 인증 확인 from metadata in context
	log.Println("check auth")
	md, ok := metadata.FromIncomingContext(ctx)
	if !ok {
		return nil, errMissingMetadata
	}

	if !validateAuth(md["authorization"]) {
		return nil, errInvalidToken
	}

	// 단순 RPC 실행을 완료하는 핸들러 호출 : 해당 메서드 호출
	return handler(ctx, req)
}
