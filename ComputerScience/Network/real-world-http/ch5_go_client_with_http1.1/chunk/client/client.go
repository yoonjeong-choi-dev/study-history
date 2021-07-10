package main

import (
	"bufio"
	"log"
	"net"
	"net/http"
	"strconv"
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
	request, _ := http.NewRequest("GET", "http://localhost:18888/chunked", nil)

	// 요청의 내용 저장
	err = request.Write(connect)
	if err != nil {
		panic(err)
	}

	// 서버의 응답을 소켓에서 받아와 저장할 bufio 생성
	reader := bufio.NewReader(connect)

	// 서버 응답의 헤더 읽어와 청크 확인
	resp, err := http.ReadResponse(reader, request)
	if err != nil {
		panic(err)
	}
	if resp.TransferEncoding[0] != "chunked" {
		panic("wrong transfer encoding : " + resp.TransferEncoding[0])
	}

	// 청크 읽어와 출력
	for {
		// Step 1 : 전송된 청크의 길이를 16진수로 받아온다
		sizeStr, err := reader.ReadBytes('\n')
		if err != nil {
			panic(err)
		}

		// 16진수로 받아온 데이터의 길이를 int로 파싱
		size, err := strconv.ParseInt(string(sizeStr[:len(sizeStr)-2]), 16, 64)
		if size == 0 {
			// 길이가 0이면 응답이 끝난 것으로 간주
			break
		}
		if err != nil {
			panic(err)
		}

		// Step 2 : 지정된 크기의 데이터만큼 읽어온다
		line := make([]byte, int(size))
		reader.Read(line)
		reader.Discard(2)
		log.Println(" ", string(line))

	}
}
