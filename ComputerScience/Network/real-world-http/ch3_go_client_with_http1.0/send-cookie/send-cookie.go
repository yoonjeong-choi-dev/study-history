package main

import (
	"log"
	"net/http"
	"net/http/cookiejar"
	"net/http/httputil"
)

func main() {
	// cookiejar : 쿠키를 저장하기 위한 인스턴스
	jar, err := cookiejar.New(nil)
	if err != nil {
		panic(err)
	}

	// http.Client : 쿠키가 저장된 cookiejar를 저장하여 전송 가능한 클라이언트 구조체
	// http 메서드를 동일한 방식으로 사용 가능
	client := http.Client{
		Jar: jar,
	}

	// 1번째 접급 : 서버에서 쿠키 받아오기
	// 2번째 이후 : 쿠키를 서버로 전송
	for i := 0; i < 2; i++ {
		resp, err := client.Get("http://localhost:18888/cookie")
		if err != nil {
			panic(err)
		}

		dump, err := httputil.DumpResponse(resp, true)
		if err != nil {
			panic(err)
		}

		log.Println(string(dump))
	}

}
