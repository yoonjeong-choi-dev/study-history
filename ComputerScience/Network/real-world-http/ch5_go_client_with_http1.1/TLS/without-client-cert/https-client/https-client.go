package main

import (
	"crypto/tls"
	"crypto/x509"
	"io/ioutil"
	"log"
	"net/http"
	"net/http/httputil"
)

func clientWithSystemCert() error {
	log.Println("*****************************************")
	log.Println("Check cert file in the system")
	defer log.Println("*****************************************")

	resp, err := http.Get("https://localhost:18443")

	if err != nil {
		log.Println("certification file does not exits in this system")
		return err
	}
	defer resp.Body.Close()

	dump, err := httputil.DumpResponse(resp, true)
	if err != nil {
		panic(err)
	}
	log.Println(string(dump))

	return nil
}

// 주의 사항 : go1.16.5의 x509에서는 SANs 인증서를 사용해야함
// => export GODEBUG=x509ignoreCN=0 를 임시로 사용하여 실행해야 한다
func clientWithLocalCert() {
	log.Println("*****************************************")
	log.Println("Check cert file in the local")
	defer log.Println("*****************************************")

	// 인증서 읽어오기
	cert, err := ioutil.ReadFile("../../certification-files/ca.crt")
	if err != nil {
		panic(err)
	}

	// 인증서 생성
	certPool := x509.NewCertPool()
	certPool.AppendCertsFromPEM(cert)
	tlsConfig := &tls.Config{
		RootCAs: certPool,
	}
	tlsConfig.BuildNameToCertificate()

	// 클라이언트 정의 : 인증서를 포함시킨다
	client := &http.Client{
		Transport: &http.Transport{
			TLSClientConfig: tlsConfig,
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

func main() {
	err := clientWithSystemCert()
	if err != nil {
		clientWithLocalCert()
	}
}
