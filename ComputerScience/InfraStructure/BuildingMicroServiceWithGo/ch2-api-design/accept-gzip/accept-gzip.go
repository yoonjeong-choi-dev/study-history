package main

import (
	"compress/gzip"
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"strings"
)

var name string

// 요청 및 응답 구조체
type EchoDto struct {
	Message string `json:"message"`
}

// gzip 압축을 위한 Write 인터페이스를 구현한 응답용 Writer
type GzipResponseWriter struct {
	gw *gzip.Writer
	http.ResponseWriter
}

// gzip.Writer 메서드 구현
func (grw GzipResponseWriter) Write(b []byte) (int, error) {
	// Content-Type이 정의되지 않은 경우 본문을 통해 콘텐츠 타입 유추하여 Content-Type 설정
	if _, ok := grw.Header()["Content-Type"]; !ok {
		grw.Header().Set("Content-Type", http.DetectContentType(b))
	}
	return grw.gw.Write(b)
}

// gzip과 http 라이터의 버퍼 flush
func (grw GzipResponseWriter) Flush() {
	// gzip flush
	grw.gw.Flush()

	// http Writer flush
	if fw, ok := grw.ResponseWriter.(http.Flusher); ok {
		fw.Flush()
	}
}

/*
GZipHandler 핸들러 구조체
- gzip 헤더가 있는 경우 GzipResponseWriter를 통해 압축
- gzip 헤더가 없는 경우, 역할을 위임하여 next 핸들러에서 표준 ResponseWriter 호출
*/
type GZipHandler struct {
	next http.Handler
}

func (gh *GZipHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	// Accept-Encoding 헤더 확인
	encodingsHeader := r.Header.Get("Accept-Encoding")

	// 헤더 타입에 따라 역할 위임
	if strings.Contains(encodingsHeader, "gzip") {
		gh.serveGzipped(w, r)
	} else if strings.Contains(encodingsHeader, "deflate") {
		log.Panic("Deflate not implemented")
	} else {
		gh.servePlain(w, r)
	}
}

func (gh *GZipHandler) serveGzipped(w http.ResponseWriter, r *http.Request) {
	// gzip 압축을 위한 Writer 객체 생성
	gzw := gzip.NewWriter(w)
	defer gzw.Close()

	w.Header().Set("Content-Encoding", "gzip")

	// 다음 핸들러에게 역할 위임 : 구현한 Gzip Writer로 응답
	gh.next.ServeHTTP(GzipResponseWriter{gzw, w}, r)
}

func (gh *GZipHandler) servePlain(w http.ResponseWriter, r *http.Request) {
	// 다음 핸들러에게 역할 위임 : 표준 Writer로 응답
	gh.next.ServeHTTP(w, r)
}

func NewGzipHandler(next http.Handler) http.Handler {
	return &GZipHandler{next}
}

// 최상위 핸들러
func EchoHandler(rw http.ResponseWriter, r *http.Request) {
	// 요청 json 파싱하기 위한 디코더 생성
	var request EchoDto
	decoder := json.NewDecoder(r.Body)

	err := decoder.Decode(&request)
	if err != nil {
		http.Error(rw, "Bad request - Unvalid JSON in Body", http.StatusBadRequest)

		// 디코더 에러 발생 시, 헨들러 체인 종료
		return
	}

	response := EchoDto{Message: "Echo : " + request.Message}

	encoder := json.NewEncoder(rw)
	encoder.Encode(response)
}

func main() {
	port := 8080

	http.Handle("/", NewGzipHandler(http.HandlerFunc(EchoHandler)))

	log.Printf("Server starting on port %v\n", port)
	log.Fatal(http.ListenAndServe(fmt.Sprintf(":%v", port), nil))
}
