package main

import (
	"log"
	pb "ordermanagement/client/order"

	"google.golang.org/grpc"
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
	client := &Client{grpcClient: pb.NewOrderManagementClient(conn)}
	client.Main()

}
