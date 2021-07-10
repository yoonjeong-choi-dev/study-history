package main

import (
	"fmt"
	"log"
	"net/http"
	"net/http/httputil"
)

func handler(w http.ResponseWriter, r *http.Request) {
	dump, err := httputil.DumpRequest(r, true)
	if err != nil {
		http.Error(w, fmt.Sprint(err), http.StatusInternalServerError)
		return
	}

	fmt.Println(string(dump))
	fmt.Fprintf(w, "<html><body>hello with HTTPS</body></html>")
}

func main() {
	http.HandleFunc("/", handler)
	log.Println("Start https listening :18443")

	// TLS 서버 리스너 생성 : 서버 인증서와 비밀키 이용
	err := http.ListenAndServeTLS(":18443", "../../certification-files/server.crt", "../../certification-files/server.key", nil)
	if err != nil {
		log.Println(err)
	}
}
