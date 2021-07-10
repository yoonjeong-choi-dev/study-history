package main

import (
	"bufio"
	"bytes"
	"io"
	"log"
	"net/http"
)

func main() {
	resp, err := http.Get("http://localhost:18888/chunked")
	if err != nil {
		panic(err)
	}
	defer resp.Body.Close()

	reader := bufio.NewReader(resp.Body)
	for {
		// 개행 문자 기준으로 서버 응답 읽기
		line, err := reader.ReadBytes('\n')
		if err == io.EOF {
			break
		}

		log.Println(string(bytes.TrimSpace(line)))

	}
}
