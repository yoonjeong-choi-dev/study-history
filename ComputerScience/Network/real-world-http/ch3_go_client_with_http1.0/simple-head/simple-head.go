package main

import (
	"log"
	"net/http"
)

func main() {
	// 헤더만 요청 : 바디는 수신받지 않는다
	resp, err := http.Head("http://localhost:18888")
	if err != nil {
		panic(err)
	}

	log.Println("Status: ", resp.Status)
	log.Println("Headers: ", resp.Header)
}
