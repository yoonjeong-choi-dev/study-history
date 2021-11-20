#!/bin/bash

# generate client code
mkdir ../client/order
protoc --go_out=../client/order --go_opt=paths=source_relative \
    --go-grpc_out=../client/order --go-grpc_opt=paths=source_relative \
    order_management.proto

# generate server code
mkdir ../service/order
protoc --go_out=../service/order --go_opt=paths=source_relative \
    --go-grpc_out=../service/order --go-grpc_opt=paths=source_relative \
    order_management.proto

# update go module
cd ../client
go mod tidy

cd ../service
go mod tidy