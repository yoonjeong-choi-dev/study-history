package main

import (
	"context"
	"fmt"
	"log"
	pb "ordermanagement/client/order"
	"time"

	"google.golang.org/grpc"
	"google.golang.org/grpc/metadata"
)

const (
	serverAddress = "localhost:50051"
)

func main() {
	// set the connection
	conn, err := grpc.Dial(serverAddress, grpc.WithInsecure())
	if err != nil {
		log.Fatalf("Cannot connect to server : %v", err)
	}
	defer conn.Close()

	// create client
	client := pb.NewOrderManagementClient(conn)

	// 서버로 전송할 메타데이터 생성
	clientMeta := metadata.Pairs(
		"timestamp", time.Now().Format(time.RFC1123),
		"name", "YJ Choi",
	)

	// 생성한 메타데이터로 컨텍스트 생성
	metaContext := metadata.NewOutgoingContext(context.Background(), clientMeta)

	// 해당 메타데이터를 컨텍스트를 통해 헤더에 포함시켜 요청
	var header, trailer metadata.MD // 서버 응답 메타데이터를 저장하는 참조 변수
	order := pb.Order{Items: []string{"Iphone 12 Purle", "Apple Watch SE"}, Description: "My Items", Destination: "Seoul", Price: 1230.0}
	res, addOrderError := client.AddOrder(metaContext, &order, grpc.Header(&header), grpc.Trailer(&trailer))

	if addOrderError != nil {
		fmt.Printf("AddOrder Error : %v\n", addOrderError)
	}

	// 서버 응답에서 메타데이터 읽기
	fmt.Println("AddOrder Response -> ", res.Value)

	if t, ok := header["timestamp"]; ok {
		fmt.Printf("timestamp from server header:\n")
		for i, e := range t {
			fmt.Printf(" %d. %s\n", i, e)
		}
	} else {
		fmt.Println("timestamp expected but doesn't exist in server metadata")
	}
	if l, ok := header["server"]; ok {
		fmt.Printf("server from server header:\n")
		for i, e := range l {
			fmt.Printf(" %d. %s\n", i, e)
		}
	} else {
		fmt.Println("location expected but doesn't exist in server metadata")
	}
}
