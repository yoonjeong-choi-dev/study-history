package main

import (
	"context"
	"encoding/json"
	"fmt"
	"log"
	"net/http"
)

func main() {
	port := 8080

	// 함수를 전달하는 핸들러 등록 : 라우팅
	http.HandleFunc("/helloWorldHandlerLegacy", helloWorldHandlerLegacy)

	// Handler 인터페이스 구현체를 전달하는 핸들러 등록
	myHandler := newValidateRequestHandler(newHelloWorldHandler())
	http.Handle("/hello", myHandler)

	// 서버 오픈
	log.Printf("Server starting on port %v\n", port)
	log.Fatal(http.ListenAndServe(fmt.Sprintf(":%v", port), nil))
}

// 응답 구조체 정의
type helloWorldResponse struct {
	Message string `json:"message"` // json 마샬에서 사용할 프로퍼티 이름을 필드 태그를 통해 정의
}

// 요청 구조체 정의
type helloWorldRequest struct {
	Name string `json:"name"`
}

// 컨텍스트로 넘길 데이터
// 단순히 string으로 넘기는 경우, 패키지 내에서 "name"이라는 키가 중복되어 overwrite 되는 문제 발생
// 해당 패키지에서는 하나의 키 값만을 컨텍스트에서 사용하지만, 규모가 큰 패키지의 경우 이런 방식으로 키 분리 필요
// cf) DTO
type validationContextKey string

/*
1. 요청의 유효성 검증을 위한 Handler 인터페이스 구현체
- 다음 작업을 위한 핸들러를 포함 : 유효성 검사 후, next 핸들러에게 역할 위임
	- 요청의 유효성 검증과 응답을 보내는 핸들러를 분리하는 것
- Handler 인터페이스 구현체는 http.Handle에 등록
	- 유효성 검증이 최우선 프로세스이기 때문
	- 검증 이후, 응답 역할을 위임한 next 핸들러로 자신의 데이터를 보냄
- ServeHTTP
	- Handler.ServeHTTP 구현
	- Go 에서의 인터페이스 구현체 구현 방식
-	newValidateRequestHandler
	- 해당 Handler 인터페이스 구현체를 생성하는 함수
	- 유효성 검증 후, 구조체에 들어 있는 next에게 역할 위임
	- 여기서는 helloWorldHandler 에게 역할 위힘
*/
type validateRequestHandler struct {
	next http.Handler
}

func (h validateRequestHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	// 요청 json 파싱하기 위한 디코더 생성
	var request helloWorldRequest
	decoder := json.NewDecoder(r.Body)

	err := decoder.Decode(&request)
	if err != nil {
		http.Error(w, "Bad request - Unvalid JSON in Body", http.StatusBadRequest)

		// 디코더 에러 발생 시, 헨들러 체인 종료
		return
	}

	// 다음 핸들러에게 데이터를 넘기기 위해 컨텍스트 생성 및 Response 객체에 저장
	resquestContext := context.WithValue(r.Context(), validationContextKey("name"), request.Name)
	r = r.WithContext(resquestContext)

	// 다음 핸들러에 요청 : 컨텍스트가 저장된 reqeust 포함
	h.next.ServeHTTP(w, r)
}

func newValidateRequestHandler(next http.Handler) http.Handler {
	return validateRequestHandler{next: next}
}

/*
2. 응답용 핸들러를 위한 Handler 인터페이스 구현체
- 유효성 검증을 마친 데이터는 http.Reqeust 매개변수를 통해 들어온다
*/
type helloWorldHandler struct{}

func (h helloWorldHandler) ServeHTTP(rw http.ResponseWriter, r *http.Request) {
	// 요청(이전 핸들러)에서 넘긴 컨텍스트에서 데이터 추출
	requestName := r.Context().Value(validationContextKey("name")).(string)

	response := helloWorldResponse{Message: "Hello : " + requestName}

	encoder := json.NewEncoder(rw)
	encoder.Encode(response)
}

func newHelloWorldHandler() http.Handler {
	return helloWorldHandler{}
}

// json 기반의 요청 및 응답을 구현한 핸들러 등록 함수
func helloWorldHandlerLegacy(w http.ResponseWriter, r *http.Request) {

	// 요청 json 파싱하기 위한 디코더 생성
	var request helloWorldRequest
	decoder := json.NewDecoder(r.Body)

	// 생성한 디코더를 통해 body의 json 파싱
	err := decoder.Decode(&request)
	if err != nil {
		http.Error(w, "Bad request - Unvalid JSON in Body", http.StatusBadRequest)
		return
	}

	// 요청에서 들어온 이름 반환
	response := helloWorldResponse{Message: "Hello World~, " + request.Name}

	// Write 인터페이스를 상속받은 모든 Writer에 대해 JSON을 바로 쓸 수 있는 Encoder 객체 반환
	encoder := json.NewEncoder(w)

	// Encoder를 통해 응답에 json 쓰기
	encoder.Encode(&response)
}
