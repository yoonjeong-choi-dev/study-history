package main

import (
	"crypto/tls"
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
	// 클라이언트에게 인증서를 요구하는 서버 설정
	server := &http.Server{
		TLSConfig: &tls.Config{
			ClientAuth: tls.RequireAndVerifyClientCert,
			MinVersion: tls.VersionTLS12,
		},
		Addr: ":18443",
	}

	http.HandleFunc("/", handler)
	log.Println("Start https listening :18443")

	// TLS 서버 리스너 생성 : 서버 인증서와 비밀키 이용
	err := server.ListenAndServeTLS("../../certification-files/server.crt", "../../certification-files/server.key")
	if err != nil {
		log.Println(err)
	}
}
