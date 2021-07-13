package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
)

var image []byte

// 서버 푸시에 사용할 이미지 로드
func init() {
	var err error
	image, err = ioutil.ReadFile("./golang.png")
	if err != nil {
		panic(err)
	}
}

// HTML을 브라우저로 송신 : 이미지 확인용
func handlerHTML(w http.ResponseWriter, r *http.Request) {
	// 서버 푸시를 위해 Puhser로 캐스팅(http/2 지원시 푸시)
	// 청크(ch5)에서 flusher로 캐스팅한 것과 유사
	pusher, ok := w.(http.Pusher)
	if ok {
		log.Println("Server push!!")
		pusher.Push("/image", nil)
	}

	w.Header().Add("Content-Type", "text/html")
	fmt.Fprintf(w, `<html><body><img src="/image"></body></html>`)
}

func handlerImage(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "image/png")
	w.Write(image)
}

// GODEBUG=http2sever=0을 지정하고 테스트해보자!
func main() {
	//var httpServer http.Server

	http.HandleFunc("/", handlerHTML)
	http.HandleFunc("/image", handlerImage)

	log.Println("start http listening :18443")

	err := http.ListenAndServeTLS(":18443", "server.crt", "server.key", nil)
	log.Println(err)
	// 서버 포트 설정
	//httpServer.Addr = ":18443"
	//log.Println(httpServer.ListenAndServe())

}
