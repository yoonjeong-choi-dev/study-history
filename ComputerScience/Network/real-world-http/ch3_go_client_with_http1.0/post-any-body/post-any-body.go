package main

import (
	"log"
	"net/http"
	"os"
	"strings"
)

func main() {
	post_file()
	post_string()
}

func post_file() {
	log.Println("============== Post local file ==============")

	// 전송할 파일 로드
	file, err := os.Open("./test_file.txt")
	if err != nil {
		panic(err)
	}

	// XMLHttpRequest 이용하여 데이터 송신
	resp, err := http.Post("http://localhost:18888", "text/plain", file)
	if err != nil {
		panic(err)
	}
	log.Println("Status: ", resp.Status)

	log.Println("==============================================")
}

func post_string() {
	log.Println("================= Post String =================")

	// 전송할 문자열을 io.Reader 인터페이스화
	reader := strings.NewReader("Send this to the server")

	// XMLHttpRequest 이용하여 데이터 송신
	resp, err := http.Post("http://localhost:18888", "text/plain", reader)
	if err != nil {
		panic(err)
	}
	log.Println("Status: ", resp.Status)

	log.Println("==============================================")
}
