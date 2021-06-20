package main

import (
	"log"
	"net/http"
	"net/http/httputil"
)

func main() {

	// 클라이언트 생성
	client := &http.Client{}

	// 자유로운 메서드 전송을 위한 Request 구조체 생성 및 설정
	reqeust, err := http.NewRequest("DELETE", "http://localhost:18888", nil)
	if err != nil {
		panic(reqeust)
	}

	// 클라이언트를 통해 기설정한 리퀘스트 전송
	resp, err := client.Do(reqeust)
	if err != nil {
		panic(err)
	}

	dump, err := httputil.DumpResponse(resp, true)
	if err != nil {
		panic(err)
	}

	log.Println(string(dump))
}
