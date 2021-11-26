package main

import (
	"log"
	pb "ordermanagement/client/order"

	"go.opencensus.io/plugin/ocgrpc"
	"go.opencensus.io/stats/view"
	"google.golang.org/grpc"
)

const (
	serverAddress = "localhost:50051"
)

func main() {
	// 수집된 데이터를 보내기 위한 익스포터 등록 : 콘솔에 기록
	// 콘솔에서 작업을 수행해야하므로 해당 익스포터는 무시
	//view.RegisterExporter(&exporter.PrintExporter{})

	// 클라리언트 요청 수를 수집하기 위한 뷰 등록 : 기본 서비스 뷰
	if err := view.Register(ocgrpc.DefaultClientViews...); err != nil {
		log.Fatalf("Fail to regigster a view : %v", err)
	}

	// 통계 핸들러와 함계 서버에 대한 연결 설정
	conn, err := grpc.Dial(serverAddress, grpc.WithStatsHandler(&ocgrpc.ClientHandler{}), grpc.WithInsecure())
	if err != nil {
		log.Fatalf("Cannot connect to server : %v", err)
	}
	defer conn.Close()

	// create client
	client := &Client{grpcClient: pb.NewOrderManagementClient(conn)}
	client.Main()

}
