package main

import (
	"log"
	"net/http"
	"net/url"
)

func main() {
	// POST를 이용해 전송할 폼 데이터 정의
	values := url.Values{
		"test": {"value"},
	}

	// PostForm : x-www-form-urlencoded 형식(인코딩 변경 x)의 폼 데이터 전송
	// 인코딩 : 알파펫, 숫자, *, -, ., _ 를 제외한 특수 문자들을 변환하여 전송
	//         => 구분 문자가 데이터에 들어있어도 서버에서 복원 가능
	// Go의 경우, RFC 3986 규칙에 따라 url 인코딩
	resp, err := http.PostForm("http://localhost:18888", values)
	if err != nil {
		// 전송 실패
		panic(err)
	}

	log.Println("Status:", resp.Status)
}
