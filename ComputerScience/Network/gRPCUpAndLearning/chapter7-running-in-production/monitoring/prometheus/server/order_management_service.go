package main

import (
	"context"
	"fmt"
	"io"
	"log"
	pb "ordermanagement/service/order"
	"strings"

	"github.com/gofrs/uuid"
	wrapper "github.com/golang/protobuf/ptypes/wrappers"
	"github.com/prometheus/client_golang/prometheus"
	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
)

// 제품 저장을 위한 로컬 스토리지
type service struct {
	orderMap       map[string]*pb.Order
	OrderBatchSize int
	pb.UnimplementedOrderManagementServer
	CustomMetric *prometheus.CounterVec
}

func (s *service) Init() {
	if s.orderMap == nil {
		s.orderMap = make(map[string]*pb.Order)
	}

	// 생성자에서 할당하지 않았으면 디폴트로 3 지정
	if s.OrderBatchSize == 0 {
		s.OrderBatchSize = 3
	}
}

func (s *service) GenerateSampleData() {
	s.orderMap["102"] = &pb.Order{Id: "102", Items: []string{"Google Pixel 3A", "Mac Book Pro"}, Destination: "Mountain View, CA", Price: 1800.00}
	s.orderMap["103"] = &pb.Order{Id: "103", Items: []string{"Apple Watch S4"}, Destination: "San Jose, CA", Price: 400.00}
	s.orderMap["104"] = &pb.Order{Id: "104", Items: []string{"Google Home Mini", "Google Nest Hub"}, Destination: "Mountain View, CA", Price: 400.00}
	s.orderMap["105"] = &pb.Order{Id: "105", Items: []string{"Amazon Echo"}, Destination: "San Jose, CA", Price: 30.00}
	s.orderMap["106"] = &pb.Order{Id: "106", Items: []string{"Amazon Echo", "Apple iPhone XS"}, Destination: "Mountain View, CA", Price: 300.00}
}

// 패턴 1 : 단순 RPC
func (s *service) AddOrder(ctx context.Context, req *pb.Order) (*wrapper.StringValue, error) {
	// 커스텀 메트릭을 이용하여 동일한 배송지 개수 모니터링
	s.CustomMetric.WithLabelValues(req.Destination).Inc()

	out, err := uuid.NewV4()
	if err != nil {
		return nil, status.Errorf(codes.Internal, "Error while generating Order ID", err)
	}

	req.Id = out.String()
	s.orderMap[req.Id] = req
	log.Printf("Order Added. Id : %v", req.Id)

	return &wrapper.StringValue{Value: "Order Added: " + req.Id}, nil
}

// 패턴 1 : 단순 RPC
func (s *service) GetOrder(ctx context.Context, req *wrapper.StringValue) (*pb.Order, error) {
	value, exist := s.orderMap[req.Value]
	if exist {
		return value, status.New(codes.OK, "").Err()
	}

	keys := make([]string, 0, len(s.orderMap))
	for k := range s.orderMap {
		keys = append(keys, k)
	}

	return nil, status.Errorf(codes.NotFound, "Order does not exist", req.Value, keys)
}

// 패턴 2 : 서버 스트리밍 - 단일 요청 + 스트림 응답
func (s *service) SearchOrders(searchQuery *wrapper.StringValue, stream pb.OrderManagement_SearchOrdersServer) error {
	log.Println("SearchOrders Stream on...")
	for key, order := range s.orderMap {
		// 설명에 매칭되는 정보가 있으면 스트림에 전송
		if strings.Contains(order.Description, searchQuery.Value) {
			err := stream.Send(order)
			if err != nil {
				return fmt.Errorf("error sending message to stream : %v", err)
			}
			log.Println("Matching Order Found : " + key)
			break
		}

		for _, itemStr := range order.Items {
			// 아이템에 매칭되는 정보가 있으면 스트림에 전송
			if strings.Contains(itemStr, searchQuery.Value) {
				err := stream.Send(order)
				if err != nil {
					return fmt.Errorf("error sending message to stream : %v", err)
				}
				log.Println("Matching Order Found : " + key)
				break
			}
		}

	}
	return nil
}

// 패턴 3 : 클라이언트 스트리밍 - 스트림 요청 + 단일 응답
func (s *service) UpdateOrders(stream pb.OrderManagement_UpdateOrdersServer) error {
	updatedOrders := ""

	// 클라이언트 스트림을 순차적으로 읽으면서 처리
	for {
		order, err := stream.Recv()
		if err != nil {
			// 스트림이 끝나면, 클라이언트 스트림 취소 : 클라이언트 전송 멈추도록 요구
			if err == io.EOF {
				return stream.SendAndClose(&wrapper.StringValue{Value: "Orders :" + updatedOrders})
			} else {
				return fmt.Errorf("error reading message from stream : %v", err)
			}
		}

		// update order
		s.orderMap[order.Id] = order
		log.Printf("Order(Id : %s) is updated\n", order.Id)
		updatedOrders += order.Id + ", "
	}
}

// 패턴 4 : 양방향 스트리밍 - 스트림 요청 + 스트림 응답(서버와 클라이언트가 스트림 공유)
func (s *service) ProcessOrders(stream pb.OrderManagement_ProcessOrdersServer) error {
	curBatch := 1

	// 배송지 기준으로 결합 발송을 위한 맵
	var combinedShipmentMap = make(map[string]pb.CombinedShipment)

	// 스트림이 끝날 때까지 스트림을 읽어 배치 처리
	for {
		orderId, err := stream.Recv()
		if err != nil {
			// 스트림이 끝나면, 배송지 기준으로 주문들을 묶어서 발송
			if err == io.EOF {
				log.Printf("EOF : %s\n", orderId)

				// 각 묶인 주문들에 대한 CombinedShipment 스트림 전송
				for _, shipment := range combinedShipmentMap {
					if err := stream.Send(&shipment); err != nil {
						return err
					}
				}

				// 서버 측 스트림이 끝났음을 클라이언트에 통보
				return nil
			} else {
				return fmt.Errorf("error reading message from stream : %v", err)
			}
		}

		order, exist := s.orderMap[orderId.GetValue()]
		if !exist {
			// 해당 주문이 없는 경우에는 무시
			continue
		}

		// 배송지 기준으로 배치 처리
		destination := order.Destination
		shipment, exist := combinedShipmentMap[destination]

		if !exist {
			shipment = pb.CombinedShipment{Id: "combined - " + destination, Status: "Processed!"}
		}
		shipment.OrderList = append(shipment.OrderList, order)
		combinedShipmentMap[destination] = shipment

		// 배치 처리 완료 시
		if curBatch == s.OrderBatchSize {
			log.Println("=========== Batch ===========")
			// 결과 스트림 전송
			for _, comb := range combinedShipmentMap {
				log.Printf("Shipping : %v -> %v", comb.Id, len(comb.OrderList))
				if err := stream.Send(&comb); err != nil {
					return err
				}
			}
			// 배치 데이터 초기화
			curBatch = 1
			combinedShipmentMap = make(map[string]pb.CombinedShipment)
		} else {
			curBatch++
		}

	}
}
