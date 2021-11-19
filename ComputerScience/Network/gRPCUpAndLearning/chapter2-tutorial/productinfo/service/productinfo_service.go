package main

import (
	"context"

	pb "productinfo/service/ecommerce"

	"github.com/gofrs/uuid"
	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
)

// 제품 저장을 위한 로컬 스토리지 : (id, Product) 테이블
type prodService struct {
	productMap map[string]*pb.Product

	// ProductInfoServer는 mustEmbedUnimplementedProductInfoServer 메서드를 구현해야함
	// 해당 메서드가 빈깡통으로 구현된 RegisterProductInfoServer를 임배딩하여 사용
	pb.UnimplementedProductInfoServer
}

// AddProduct 인터페이스 구현 : Product => ProductID
func (s *prodService) AddProduct(ctx context.Context, in *pb.Product) (*pb.ProductID, error) {
	// Product Id를 uuid를 이용하여 생성
	out, err := uuid.NewV4()

	if err != nil {
		return nil, status.Errorf(codes.Internal, "Error while generating Product ID", err)
	}

	// input Product 정보에 id 추가
	in.Id = out.String()
	if s.productMap == nil {
		s.productMap = make(map[string]*pb.Product)
	}
	s.productMap[in.Id] = in

	return &pb.ProductID{Value: in.Id}, status.New(codes.OK, "").Err()
}

// GetProduct 인터페이스 구현 : ProductID => Product
func (s *prodService) GetProduct(ctx context.Context, in *pb.ProductID) (*pb.Product, error) {
	// 로컬 스토키지에서 id를 이용하여 검색
	value, exists := s.productMap[in.Value]
	if exists {
		return value, status.New(codes.OK, "").Err()
	}

	// 없는 경우 404
	return nil, status.Errorf(codes.NotFound, "Product does not exist", in.Value)
}
