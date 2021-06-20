package main

import (
	"fmt"
	"log"
	"net/http"
	"net/http/httputil"
)

func handler(writer http.ResponseWriter, req *http.Request) {
	dump, err := httputil.DumpRequest(req, true)
	if err != nil {
		http.Error(writer, fmt.Sprint(err), http.StatusInternalServerError)
		return
	}
	fmt.Println(string(dump))
	fmt.Fprintf(writer, "<html><body>Test Server</body></html>\n")
}

func main() {
	var httpServer http.Server

	// 루트 경로에 handler 등록 : 루트 경로 접속 시, handler 함수 호출
	http.HandleFunc("/", handler)
	log.Println("start http listening: 18888")

	// 서버 포트 설정
	httpServer.Addr = ":18888"
	log.Println(httpServer.ListenAndServe())
}
