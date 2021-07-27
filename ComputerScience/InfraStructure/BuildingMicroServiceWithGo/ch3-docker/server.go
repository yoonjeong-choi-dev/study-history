package main

import (
	"fmt"
	"log"
	"net/http"
)

func helloWorldHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, "Hello World\n")
}

func indexHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, "Hello Docker!\n")
}

func main() {
	port := 8080

	// 핸들러 등록 : 라우팅
	http.HandleFunc("/helloworld", helloWorldHandler)
	http.HandleFunc("/", indexHandler)

	// 서버 오픈
	log.Printf("Server starting on port %v\n", port)
	log.Fatal(http.ListenAndServe(fmt.Sprintf(":%v", port), nil))
}
