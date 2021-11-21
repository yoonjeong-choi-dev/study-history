package main

import (
	"context"
	"log"

	hello_pb "google.golang.org/grpc/examples/helloworld/helloworld"
)

type helloService struct {
	hello_pb.UnimplementedGreeterServer
}

func (s *helloService) SayHello(ctx context.Context, in *hello_pb.HelloRequest) (*hello_pb.HelloReply, error) {
	log.Println("Greeting Service - SayHello RPC")
	return &hello_pb.HelloReply{Message: "Hello~ " + in.Name}, nil
}
