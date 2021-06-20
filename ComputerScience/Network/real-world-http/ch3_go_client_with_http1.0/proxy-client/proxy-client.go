package main

import (
	"log"
	"net/http"
	"net/http/httputil"
	"net/url"
)

func main() {
	// 프록시 url 설정 : 외부 url을 GET하여도 해당 프록시 서버로 접근
	proxyUrl, err := url.Parse("http://localhost:18888")
	if err != nil {
		panic(err)
	}

	// Transport : 실제 통신을 하는 백엔드
	client := http.Client{
		Transport: &http.Transport{
			Proxy: http.ProxyURL(proxyUrl),
		},
	}

	// 프록시가 설정된 클라이언트로 외부 url 접속
	resp, err := client.Get("http://github.com")
	if err != nil {
		panic(err)
	}

	dump, err := httputil.DumpResponse(resp, true)
	if err != nil {
		panic(err)
	}

	log.Println(string(dump))
}
