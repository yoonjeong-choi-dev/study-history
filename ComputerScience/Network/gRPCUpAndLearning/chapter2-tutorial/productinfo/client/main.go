package main

import (
	"context"
	"log"
	pb "productinfo/client/ecommerce"
	"time"

	"google.golang.org/grpc"
)

const (
	serverAddress = "localhost:50051"
)

func main() {
	// grpc를 이용하여 서버와 연결 설정
	conn, err := grpc.Dial(serverAddress, grpc.WithInsecure())
	if err != nil {
		log.Fatalf("Cannot connect to server : %v", err)
	}
	defer conn.Close()

	// 서버와 연결할 클라이언트 객체 생성
	client := pb.NewProductInfoClient(conn)

	// 상품 하나를 생성
	name := "Apple Iphone 12 Purple"
	description := "YJ's cell phone"
	price := float32(1000.0)

	// 통신 컨텍스트 생성
	ctx, cancel := context.WithTimeout(context.Background(), time.Second)
	defer cancel()

	// grpc 호출 1 : AddProduct
	resp, err := client.AddProduct(ctx,
		&pb.Product{Name: name, Description: description, Price: price})
	if err != nil {
		log.Fatalf("Fail to add product: %v", err)
	}

	log.Printf("Product ID : %s added successfully!!\n", resp.Value)

	// grpc 호출 2 : GetProduct
	product, err := client.GetProduct(ctx, &pb.ProductID{Value: resp.Value})
	if err != nil {
		log.Fatalf("Fail to get product: %v\n", err)
	}
	log.Printf("Product :  %s", product.String())
}
