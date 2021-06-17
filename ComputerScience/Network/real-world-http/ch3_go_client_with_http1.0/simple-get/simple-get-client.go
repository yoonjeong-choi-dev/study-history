package main

import (
	"io/ioutil"
	"log"
	"net/http"
)

func main() {
	// GET 메서드 전송
	// resp : 서버에서 오는 다양한 정보(헤더, 바디, 상태 코드 etc)를 담는 http.Response 오브젝트
	resp, err := http.Get("http://localhost:18888")

	// 오류 처리 : nil 값으로 확인
	if err != nil {
		// 라이브러리화 하는 경우, 해당 에러를 반환
		panic(err)
	}

	// 리소스 정리 코드 : defer는 해당 스코프를 벗어 날 때 동작
	defer resp.Body.Close()

	// GET을 통해 수신 받은 정보 출력 : 헤더, 상태 및 상태 코드
	log.Println("Headers: \n", resp.Header)
	log.Println("Status: ", resp.Status)
	log.Println("StatusCode: ", resp.StatusCode)

	// 바디의 내용 출력
	body, err := ioutil.ReadAll((resp.Body))
	if err != nil {
		panic(err)
	}
	log.Println(string(body))
}
