package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"strconv"

	"building_msa_with_go/ch1/rpc/simple-example/contract"
)

type HTTPResponseForRPC struct {
	Id       string                      `json:"id"`
	Response contract.HelloWorldResponse `json:"result"`
	Error    error                       `json:"error"`
}

func main() {
	var yourInput string

	for {
		fmt.Print("요청 입력(Q: 나가기): ")
		fmt.Scanln(&yourInput)

		if yourInput == "Q" {
			break
		}
		response := PerformRequest(yourInput)
		fmt.Println(response.Message)
	}
}

const PORT_NUMBER = 1234

func PerformRequest(clientInput string) contract.HelloWorldResponse {
	// POST 요청을 위한 주소 및 데이터 설정
	url := "http://localhost:" + strconv.Itoa(PORT_NUMBER)
	data := fmt.Sprintf("{\"id\": 1, \"method\": \"HelloWorldHandler.HelloWorld\", \"params\": [{\"name\":\"%s\"}]}", clientInput)

	// POST 요청
	r, err := http.Post(
		url,
		"application/json",
		bytes.NewBuffer([]byte(data)),
	)
	if err != nil {
		fmt.Println("POST Request Error")
		log.Fatal(err)
	}
	defer r.Body.Close()

	// 서버 응답
	decoder := json.NewDecoder(r.Body)
	var response HTTPResponseForRPC
	decoder.Decode(&response)

	return response.Response
}
