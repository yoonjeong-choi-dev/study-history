package main

import (
	"bytes"
	"compress/gzip"
	"fmt"
	"io/ioutil"
	"net/http"
)

var serverURL string = "http://localhost:8080"

// 응답 구조체
type EchoDto struct {
	Message string `json:"message"`
}

func main() {
	PlainRequest()
	GzipRequest()
}

func PrintResponseBodyInfo(resp *http.Response) []byte {
	fmt.Println("response Status:", resp.Status)
	fmt.Println("response Headers:", resp.Header)
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		panic(err)
	}

	fmt.Println("response Body:", string(body))
	return body
}

func PlainRequest() {

	var jsonStr = []byte(`{"message":"This is a plain text"}`)
	req, err := http.NewRequest("POST", serverURL, bytes.NewBuffer(jsonStr))
	if err != nil {
		panic(err)
	}

	req.Header.Set("Content-Type", "application/json")

	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		panic(err)
	}
	defer resp.Body.Close()

	PrintResponseBodyInfo(resp)
}

func GzipRequest() {
	var jsonStr = []byte(`{"message":"Gzip Encoding"}`)
	req, err := http.NewRequest("POST", serverURL, bytes.NewBuffer(jsonStr))
	if err != nil {
		panic(err)
	}

	req.Header.Set("Content-Type", "application/json")
	req.Header.Set("Accept-Encoding", "gzip")

	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		panic(err)
	}
	defer resp.Body.Close()

	body := PrintResponseBodyInfo(resp)

	reader := bytes.NewReader([]byte(body))
	gzreader, err := gzip.NewReader(reader)
	if err != nil {
		panic(err)
	}

	plainBody, err := ioutil.ReadAll(gzreader)
	if err != nil {
		panic(err)
	}

	fmt.Println("Plain Body:", string(plainBody))
}
