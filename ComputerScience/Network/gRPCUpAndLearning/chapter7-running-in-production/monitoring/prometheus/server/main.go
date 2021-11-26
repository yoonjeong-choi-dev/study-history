package main

import (
	"fmt"
	"log"
	"net"
	"net/http"
	pb "ordermanagement/service/order"

	"google.golang.org/grpc"

	"github.com/grpc-ecosystem/go-grpc-prometheus" // 프로메테우스 모니터링 지원을 위해 미리 정의된 인터셉터들
	"github.com/prometheus/client_golang/prometheus"
	"github.com/prometheus/client_golang/prometheus/promhttp"
)

const (
	port = ":50051"
)

var (
	// 메트릭 레지스트리(데이터 수집기들 컬렉션)
	register = prometheus.NewRegistry()

	// 표준 서버 메트릭(라이브러리 제공)
	grpcMetrics = grpc_prometheus.NewServerMetrics()

	// 커스텀 메트릭 정의
	customizedCounterMetric = prometheus.NewCounterVec(prometheus.CounterOpts{
		Name: "order_manager_server_handle_count",
		Help: "Total number of RPCs handled on the server.",
	}, []string{"name"})
)

// 패키지 로드 시, 가장 먼저 호출되는 함수
func init() {
	// 메트릭 레지스트리에 표준 및 커스텀 메트릭 등록
	register.MustRegister(grpcMetrics, customizedCounterMetric)
}

func main() {
	// 서비스 초기화
	orderManager := &service{OrderBatchSize: 3, CustomMetric: customizedCounterMetric}
	orderManager.Init()
	orderManager.GenerateSampleData()

	// TCP 리스너
	listener, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalf("Failed to listen: %v", err)
	}

	// 모니터링 인터셉터를 추가한 grpc 서비스 등록
	s := grpc.NewServer(
		grpc.StreamInterceptor(grpcMetrics.StreamServerInterceptor()),
		grpc.UnaryInterceptor(grpcMetrics.UnaryServerInterceptor()),
	)
	pb.RegisterOrderManagementServer(s, orderManager)

	// 메트릭 초기화
	grpcMetrics.InitializeMetrics(s)

	// 프로메테우스 용 HTTP 서버 생성
	// localhost:9092/metrics
	httpServer := &http.Server{
		Handler: promhttp.HandlerFor(register, promhttp.HandlerOpts{}),
		Addr:    fmt.Sprintf("0.0.0.0:%d", 9092),
	}
	go func() {
		if err := httpServer.ListenAndServe(); err != nil {
			log.Fatalf("Fail to open Monitoring server : %v", err)
		}
	}()

	log.Printf("Starting gRPC listener on port " + port)
	if err := s.Serve(listener); err != nil {
		log.Fatalf("Fail to start : %v", err)
	}
}
