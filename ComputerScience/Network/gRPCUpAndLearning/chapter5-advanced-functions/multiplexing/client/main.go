package main

import (
	"context"
	"fmt"
	"log"
	pb "ordermanagement/client/order"
	"time"

	hello_pb "google.golang.org/grpc/examples/helloworld/helloworld"

	"google.golang.org/grpc"
)

const (
	serverAddress = "localhost:50051"
)

func main() {
	// set the connection : 두 클라이언트가 연결을 공유
	conn, err := grpc.Dial(serverAddress, grpc.WithInsecure())
	if err != nil {
		log.Fatalf("Cannot connect to server : %v", err)
	}
	defer conn.Close()

	// create client 1
	client1 := pb.NewOrderManagementClient(conn)

	// create client 2
	client2 := hello_pb.NewGreeterClient(conn)

	// Service 1 Request
	ctx, cancel := context.WithTimeout(context.Background(), time.Second*5)
	defer cancel()

	fmt.Println("Reqeust Service 1 : Order Management")
	order := pb.Order{Items: []string{"Iphone 12 Purle", "Apple Watch SE"}, Description: "My Items", Destination: "Seoul", Price: 1230.0}
	res1, addOrderError := client1.AddOrder(ctx, &order)

	if addOrderError != nil {
		fmt.Printf("AddOrder Error : %v\n", addOrderError)
	} else {
		fmt.Println("AddOrder Response -> ", res1.Value)
	}

	// Service 2 Request
	helloCtx, helloCancle := context.WithTimeout(context.Background(), time.Second*5)
	defer helloCancle()

	fmt.Println("Reqeust Service 2 : Greeting")
	res2, helloError := client2.SayHello(helloCtx, &hello_pb.HelloRequest{Name: "Yoonjeong Choi"})
	if helloError != nil {
		fmt.Printf("SayHello Error : %v\n", helloError)
	} else {
		fmt.Println("SayHello Response -> ", res2.Message)
	}
}
