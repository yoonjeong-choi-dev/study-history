package main

import (
	"crypto/tls"
	"log"
	"net/http"
	"net/http/httputil"
)

func main() {
	// 인증서 및 비밀키 가져오기
	cert, err := tls.LoadX509KeyPair("../../certification-files/client.crt", "../../certification-files/client.key")
	if err != nil {
		panic(err)
	}

	// 클라이언트 정의 : 인증서 및 비밀 키를 포함시킨다
	client := &http.Client{
		Transport: &http.Transport{
			TLSClientConfig: &tls.Config{
				Certificates: []tls.Certificate{cert},
			},
		},
	}

	// 통신
	resp, err := client.Get("https://localhost:18443")
	if err != nil {
		panic(err)
	}
	defer resp.Body.Close()

	dump, err := httputil.DumpResponse(resp, true)
	if err != nil {
		panic(err)
	}
	log.Println(string(dump))
}
