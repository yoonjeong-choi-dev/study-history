package main

import (
	"context"
	"fmt"
	"log"
	pb "ordermanagement/client/order"
	"time"

	epb "google.golang.org/genproto/googleapis/rpc/errdetails"
	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"

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
	client := pb.NewOrderManagementClient(conn)

	ctx, cancel := context.WithTimeout(context.Background(), time.Second*5)
	defer cancel()

	// Invalid Request
	order1 := pb.Order{Id: "-1", Items: []string{"Error Item"}, Description: "Error Test", Destination: "Seoul", Price: 123.0}
	res, addOrderError := client.AddOrder(ctx, &order1)

	// Error Handling
	if addOrderError != nil {
		errorCode := status.Code(addOrderError)

		// 특정 에러에 대한 예외 처리
		if errorCode == codes.InvalidArgument {
			fmt.Printf("Invalid Argument Error : %s\n", errorCode)

			// 에러 세부 사항 출력
			errorStatus := status.Convert(addOrderError)
			for _, detail := range errorStatus.Details() {
				switch info := detail.(type) {
				case *epb.BadRequest_FieldViolation:
					fmt.Printf("Request Field Invalid : %s\n", info)
				default:
					fmt.Printf("Unexpected error type : %s\n", info)
				}
			}
		} else {
			fmt.Printf("Unhandled error : %s\n", errorCode)
		}

	} else {
		// 정상 처리
		fmt.Println("AddOrder Response -> ", res.Value)
	}
}
