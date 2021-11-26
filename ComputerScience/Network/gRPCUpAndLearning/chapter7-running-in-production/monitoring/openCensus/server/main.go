package main

import (
	"log"
	"net"
	"net/http"
	pb "ordermanagement/service/order"

	"go.opencensus.io/examples/exporter"
	"go.opencensus.io/plugin/ocgrpc"
	"go.opencensus.io/stats/view"
	"go.opencensus.io/zpages"
	"google.golang.org/grpc"
)

const (
	port = ":50051"
)

func main() {
	// 모니터링 서버 시작 :
	// http://127.0.0.1:8081/debug/rpcz
	// http://127.0.0.1:8081/debug/tracez
	go func() {
		mux := http.NewServeMux()
		zpages.Handle(mux, "/debug")
		log.Fatal(http.ListenAndServe("127.0.0.1:8081", mux))
	}()

	// 수집된 데이터를 보내기 위한 익스포터 등록 : 콘솔에 기록
	view.RegisterExporter(&exporter.PrintExporter{})

	// 서버 요청 수를 수집하기 위한 뷰 등록 : 기본 서비스 뷰
	if err := view.Register(ocgrpc.DefaultServerViews...); err != nil {
		log.Fatalf("Fail to regigster a view : %v", err)
	}

	// 서비스 초기화
	orderManager := &service{OrderBatchSize: 3}
	orderManager.Init()
	orderManager.GenerateSampleData()

	// TCP 리스너
	listener, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalf("Failed to listen: %v", err)
	}

	// 통계 핸들러와 함께 grpc 서비스 등록
	s := grpc.NewServer(grpc.StatsHandler(&ocgrpc.ServerHandler{}))
	pb.RegisterOrderManagementServer(s, orderManager)

	log.Printf("Starting gRPC listener on port " + port)
	if err := s.Serve(listener); err != nil {
		log.Fatalf("Fail to start : %v", err)
	}
}
