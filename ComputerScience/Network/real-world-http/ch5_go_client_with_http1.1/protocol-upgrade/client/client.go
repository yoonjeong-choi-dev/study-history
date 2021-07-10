package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io"
	"log"
	"net"
	"net/http"
	"time"
)

func main() {

	// TCP 소켓 정의
	dialer := &net.Dialer{
		Timeout:   30 * time.Second,
		KeepAlive: 30 * time.Second,
	}

	// 서버로의 소켓 연결
	connect, err := dialer.Dial("tcp", "localhost:18888")
	if err != nil {
		panic(err)
	}
	defer connect.Close()

	// 소켓에 저장할 서버로의 요청 저장
	request, _ := http.NewRequest("GET", "http://localhost:18888/upgrade", nil)

	// 프로토콜 업그레이드를 위한 헤더 작성
	request.Header.Set("Connection", "Upgrade")
	request.Header.Set("Upgrade", "MyProtocol")

	// 요청의 내용 저장
	err = request.Write(connect)
	if err != nil {
		panic(err)
	}

	// 서버의 응답을 소켓에서 받아와 저장
	reader := bufio.NewReader(connect)
	response, err := http.ReadResponse(reader, request)
	if err != nil {
		panic(err)
	}

	// 서버 응답의 상태 및 헤더 출력
	log.Println("Status :", response.Status)
	log.Println("Headers: ", response.Header)

	// 소켓 통신
	counter := 100
	for {
		// 서버 응답의 body에서 개행 문자를 기준으로 데이터를 읽어와 출력(<- 부분)
		data, err := reader.ReadBytes('\n')
		if err == io.EOF {
			break
		}
		fmt.Println("<-(From Server)", string(bytes.TrimSpace(data)))

		// 소켓을 통해 클라이언트의 counter를 서버로 요청
		fmt.Fprintf(connect, "%d\n", counter)
		fmt.Println("-> (To Server)", counter)
		counter = counter - 10
	}
}
