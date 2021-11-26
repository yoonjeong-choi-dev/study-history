package main

import (
	"fmt"
	"log"
	"net/http"
	pb "ordermanagement/client/order"

	"github.com/grpc-ecosystem/go-grpc-prometheus" // 프로메테우스 모니터링 지원을 위해 미리 정의된 인터셉터들
	"github.com/prometheus/client_golang/prometheus"
	"github.com/prometheus/client_golang/prometheus/promhttp"
	"google.golang.org/grpc"
)

const (
	serverAddress = "localhost:50051"
)

func main() {
	// 메트릭 레지스트리(데이터 수집기들 컬렉션)
	register := prometheus.NewRegistry()

	// 표준 클라이언트 메트릭(라이브러리 제공)
	grpcMetrics := grpc_prometheus.NewClientMetrics()

	// 메트릭 레지스트리에 표준 메트릭 등록
	register.MustRegister(grpcMetrics)

	// 메트릭 인터셉터를 포함시킨 연결 설정
	conn, err := grpc.Dial(serverAddress, grpc.WithUnaryInterceptor(grpcMetrics.UnaryClientInterceptor()), grpc.WithInsecure())
	if err != nil {
		log.Fatalf("Cannot connect to server : %v", err)
	}
	defer conn.Close()

	// 프로메테우스 용 HTTP 서버 생성
	// localhost:9092/metrics
	httpServer := &http.Server{
		Handler: promhttp.HandlerFor(register, promhttp.HandlerOpts{}),
		Addr:    fmt.Sprintf("0.0.0.0:%d", 9094),
	}
	go func() {
		if err := httpServer.ListenAndServe(); err != nil {
			log.Fatalf("Fail to open Monitoring server : %v", err)
		}
	}()

	// create client
	client := &Client{grpcClient: pb.NewOrderManagementClient(conn)}
	client.Main()

}
