package main

import (
	"log"
	"net/http"
	"net/http/httputil"
)

func main() {
	// file 스키마 이용을 위한 트랜스포트 생성 및 파일 스키마 등록
	transport := &http.Transport{}
	transport.RegisterProtocol("file", http.NewFileTransport((http.Dir("."))))

	// 생성한 트랜스포트를 등록한 클라이언트 생성 및 GET 호출(현재 디렉토리 파일 접근)
	client := http.Client{
		Transport: transport,
	}
	resp, err := client.Get("file://./test_file.txt")
	if err != nil {
		panic(err)
	}

	dump, err := httputil.DumpResponse(resp, true)
	if err != nil {
		panic(err)
	}
	log.Println(string(dump))
}
