package main

import (
	"bytes"
	"io"
	"log"
	"mime/multipart"
	"net/http"
	"net/textproto"
	"os"
)

// multipart : 한 번의 요청으로 복수의 데이터(파일) 전송
func main() {
	// 멀티파트에 설정할 바이트열을 저장할 버퍼
	var buffer bytes.Buffer

	// 버퍼에 데이터를 저장하는 writer 생성
	writer := multipart.NewWriter(&buffer)

	// 데이터 1 : 문자열
	writer.WriteField("name", "user123")

	// 데이터 2 : 사진
	// Step 0 : MIME 타입 설정
	part := make(textproto.MIMEHeader)
	part.Set("Content-Type", "image/png")
	part.Set("Content-Disposition", `form-data; name="thumbnail", filenmae="golang.png"`)

	// Step 1 : 버퍼에 사진 데이터 저장을 위해 MIME 타입이 설정된 writer 생성
	fileWriter, err := writer.CreatePart(part)
	if err != nil {
		panic(err)
	}

	// Step 2 : 버퍼에 쓸 사진 데이터 로드
	readFile, err := os.Open("golang.png")
	if err != nil {
		panic(err)
	}
	defer readFile.Close()

	// Step 3 : 사진 데이터를 버퍼에 저장
	io.Copy(fileWriter, readFile)

	// 서버로 전송
	// FormDataContentType : multiPart.Writer가 생성한 난수 경계 문자열을 포함하여 Cotent-Type 헤더 생성
	resp, err := http.Post("http://localhost:18888", writer.FormDataContentType(), &buffer)
	if err != nil {
		panic(err)
	}

	log.Println("Status: ", resp.Status)
}
