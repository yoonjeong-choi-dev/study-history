package main

import (
	"bufio"
	"context"
	"fmt"
	"io"
	"log"
	"os"
	"strconv"
	"strings"
	"sync"
	"time"

	pb "ordermanagement/client/order"

	wrapper "github.com/golang/protobuf/ptypes/wrappers"
)

type Client struct {
	grpcClient pb.OrderManagementClient
	stdin      *bufio.Reader
}

func (c *Client) Main() {
	c.stdin = bufio.NewReader(os.Stdin)
	var isContinue bool
	for {
		isContinue = c.ShowMenu()

		if isContinue == false {
			return
		}
	}
}

func (c *Client) ShowMenu() bool {

	fmt.Println("\n\n<<<< Choose your service >>>>")
	fmt.Println("1. Add Order")
	fmt.Println("2. Get Order")
	fmt.Println("3. Search Orders")
	fmt.Println("4. Update Orders")
	fmt.Println("5. Process Orders")
	fmt.Println("6. Exit")

	var choice int
	var isValid bool
	for {
		fmt.Print("Your choice :")
		choice, isValid = c.inputInteger(false, 6)
		if isValid == true {
			break
		} else {
			fmt.Println("Please enter valid choice")
		}
	}

	if choice == 6 {
		return false
	}

	fmt.Printf("\n\n[ Sub Process ]\n")
	switch choice {
	case 1:
		c.AddOrder()
	case 2:
		c.GetOrder()
	case 3:
		c.SearchOrders()
	case 4:
		c.UpdateOrders()
	case 5:
		c.ProcessOrders()
	}

	return true
}

// 패턴 1 : 단순 RPC
func (c *Client) AddOrder() {

	fmt.Println("-- Order Information --")
	order := c.inputOrderInfo()

	ctx, cancel := context.WithTimeout(context.Background(), time.Second*5)
	defer cancel()

	res, err := c.grpcClient.AddOrder(ctx, order)
	if err != nil {
		fmt.Printf("\nBad Response -> %v\n", err)
	}
	if res != nil {
		fmt.Print("\nAddOrder Response -> ", res.Value)
	}
}

// 패턴 1 : 단순 RPC
func (c *Client) GetOrder() {
	fmt.Print("Enter item ID : ")
	orderId := c.inputString()

	ctx, cancel := context.WithTimeout(context.Background(), time.Second*5)
	defer cancel()

	res, err := c.grpcClient.GetOrder(ctx, &wrapper.StringValue{Value: orderId})
	if err != nil {
		fmt.Printf("\nBad Response -> %v\n", err)
	} else {
		c.PrintOrder(res)
	}
}

// 패턴 2 : 서버 스트리밍 - 단일 요청 + 스트림 응답
func (c *Client) SearchOrders() {
	fmt.Print("Enter query for items : ")
	query := c.inputString()

	ctx, cancel := context.WithTimeout(context.Background(), time.Second*5)
	defer cancel()

	// 서버에서 전송한 스트림 객체를 받아온다
	resStream, err := c.grpcClient.SearchOrders(ctx, &wrapper.StringValue{Value: query})
	if err != nil {
		fmt.Printf("Bad Response : %v\n", err)
		return
	}

	// 스트림이 끝날 때까지 계속 요청
	for {
		searchOrder, err := resStream.Recv()
		if err != nil {
			if err == io.EOF {
				break
			} else {
				fmt.Printf("Bad Response : %v\n", err)
				return
			}
		}
		c.PrintOrder(searchOrder)
	}
}

// 패턴 3 : 클라이언트 스트리밍 - 스트림 요청 + 단일 응답
func (c *Client) UpdateOrders() {
	// 사용자 입력을 받아야 하므로, 5분까지 대기
	ctx, cancel := context.WithTimeout(context.Background(), time.Minute*5)
	defer cancel()

	// 서버에 전송할 스트림 생성
	updateStream, err := c.grpcClient.UpdateOrders(ctx)
	if err != nil {
		fmt.Printf("Fail to create update stream : %v", err)
		return
	}

	var orderIdInput string
	for {
		fmt.Print("Enter item ID to update('q' to Stop): ")
		orderIdInput = c.inputString()
		if orderIdInput == "q" {
			fmt.Println("Stop to stream")
			break
		}

		order := c.inputOrderInfo()
		order.Id = orderIdInput

		// update order
		if err := updateStream.Send(order); err != nil {
			fmt.Printf("Fail to updateOrder : %v", err)
			break
		}
	}

	// 스트림을 완료했다고 서버로 전송
	updateRes, err := updateStream.CloseAndRecv()
	if err != nil {
		fmt.Printf("Fail to close updateStream : %v", err)
		return
	}

	fmt.Printf("Responpse -> %s", updateRes)
}

// 패턴 4 : 양방향 스트리밍 - 스트림 요청 + 스트림 응답
func (c *Client) ProcessOrders() {
	// 사용자 입력을 받아야 하므로, 5분까지 연결
	ctx, cancel := context.WithTimeout(context.Background(), time.Minute*5)
	defer cancel()

	// 서버에 전송할 스트림 생성
	streamProcOrder, err := c.grpcClient.ProcessOrders(ctx)
	if err != nil {
		fmt.Printf("Fail to create process stream : %v", err)
		return
	}

	var wg sync.WaitGroup
	wg.Add(2)

	go c.asyncWriteStream(streamProcOrder, &wg)
	// 서버에서 스트림을 병렬로 읽기 위한 고루틴
	go c.asyncReadStream(streamProcOrder, &wg)

	wg.Wait()
}

func (c *Client) asyncWriteStream(streamProcOrder pb.OrderManagement_ProcessOrdersClient, wg *sync.WaitGroup) {
	// 서버로 스트림 전송
	var orderIdInput string
	for {
		// 서버 스트림을 읽는 시간을 위해 잠시 대기
		time.Sleep(time.Millisecond * 100)

		fmt.Print("Enter item ID to process('q' to Stop): ")
		orderIdInput = c.inputString()
		if orderIdInput == "q" {
			fmt.Println("Stop to write stream")
			break
		}

		if err := streamProcOrder.Send(&wrapper.StringValue{Value: orderIdInput}); err != nil {
			fmt.Printf("Fail to send processOrder stream : %v", err)
			break
		}
	}

	err := streamProcOrder.CloseSend()
	if err != nil {
		fmt.Printf("Fail to close updateStream : %v", err)
		return
	}

	wg.Done()
}

func (c *Client) asyncReadStream(streamProcOrder pb.OrderManagement_ProcessOrdersClient, wg *sync.WaitGroup) {
	for {
		combinedShipment, err := streamProcOrder.Recv()
		if err == io.EOF {
			break
		}

		orders := combinedShipment.OrderList
		fmt.Println("===============================")
		fmt.Printf("Server -> Combined Shipment : ")
		for _, order := range orders {
			c.PrintOrder(order)
		}
		fmt.Println("===============================")
	}

	wg.Done()
}

func (c *Client) PrintOrder(order *pb.Order) {
	fmt.Println("\n[ Order ]")
	fmt.Println("Order Id: ", order.Id)
	fmt.Println("Order Items : ", strings.Join(order.Items, ", "))
	fmt.Println("Description :", order.Description)
	fmt.Println("Destination :", order.Destination)
	fmt.Println("Price :", order.Price)
}

func (c *Client) inputInteger(isBound bool, max int) (int, bool) {
	var num int
	_, err := fmt.Scanln(&num)
	if err != nil {
		fmt.Printf("Invalid integer :%v\n", err)
		c.stdin.ReadString('\n') // flush stdin
		return 0, false
	}

	if num < 0 {
		return 0, false
	}

	if isBound && num > max {
		return 0, false
	}

	return num, true
}

func (c *Client) inputFloat() (float32, bool) {
	var input string
	_, err := fmt.Scanln(&input)
	if err != nil {
		log.Fatalf("fmt.Scanln error : %v", err)
	}

	val, err := strconv.ParseFloat(input, 32)
	if err != nil {
		fmt.Printf("%s is not float", input)
		c.stdin.ReadString('\n') // flush stdin
		return 0.0, false
	}

	ret := float32(val)

	return ret, true
}

func (c *Client) inputString() string {
	input, err := c.stdin.ReadString('\n')
	if err != nil {
		log.Fatalf("fmt.Scanln error : %v", err)
	}

	input = strings.Replace(input, "\n", "", -1)

	return input
}

func (c *Client) inputOrderInfo() *pb.Order {
	var isValid bool
	var numItems int
	for {
		fmt.Print("\nNumber of items : ")
		numItems, isValid = c.inputInteger(false, 0)

		if isValid {
			break
		} else {
			fmt.Println("Please enter positive integer")
		}
	}

	items := make([]string, 0, numItems)
	for i := 0; i < numItems; i++ {
		fmt.Printf("Enter %d-th item : ", i+1)
		item := c.inputString()
		items = append(items, item)
	}

	var description string
	fmt.Print("\nEnter description : ")
	description = c.inputString()

	var destination string
	fmt.Print("\nEnter destination : ")
	destination = c.inputString()

	var price float32
	for {
		fmt.Print("\nEnter price : ")
		price, isValid = c.inputFloat()

		if isValid {
			break
		}
	}

	order := &pb.Order{Items: items, Destination: destination, Description: description, Price: price}
	return order
}
