package main

import (
	"io/ioutil"
	"log"
	"net/http"
	"net/url"
)

func main() {
	// 쿼리 문자열 생성 : RFC와 호환성이 높은 변환 방식으로 쿼리 문자열 생성 기능 제공
	values := url.Values{
		"query": {"hello world"},
	}

	// 쿼리와 함께 GET
	resp, err := http.Get("http://localhost:18888" + "?" + values.Encode())
	if err != nil {
		panic(err)
	}
	defer resp.Body.Close()

	body, _ := ioutil.ReadAll(resp.Body)
	log.Println(string(body))
}
