package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
)

type ResponseDto struct {
	Message string `json:"message"`
}

func corsHandler(w http.ResponseWriter, r *http.Request) {

	// OPTION 메서드 : CORS 허용 헤더
	// 클라이언트는 실제 요청 전 OPTIONS 요청
	if r.Method == "OPTIONS" {
		// CORS를 허용하는 경로 설정
		w.Header().Add("Access-Control-Allow-Origin", "*")
		// CORS를 허용하는 메서드 설정
		w.Header().Add("Access-Control-Allow-Methods", "GET")
		// body가 없기 때문에 204 상태 코드 사용
		w.WriteHeader(http.StatusNoContent)
		return
	}

	// 일반 요청 처리
	response := ResponseDto{Message: "CORS allowed"}
	data, err := json.Marshal(response)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Fprint(w, string(data))
}
