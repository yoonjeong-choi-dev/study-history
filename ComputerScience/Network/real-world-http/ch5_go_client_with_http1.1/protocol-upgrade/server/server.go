package main

import (
	"fmt"
	"io"
	"log"
	"net/http"
	"time"
)

func handler(w http.ResponseWriter, r *http.Request) {
	// 헤더에는 Connection: Upgrade, Upgrade: MyProtocol 이 반드시 포함되어야 한다
	// MyProtocol : http 문맥에 벗어나는 임의의 프로토콜
	if r.Header.Get("Connection") != "Upgrade" || r.Header.Get("Upgrade") != "MyProtocol" {
		w.WriteHeader(400)
		return
	}

	fmt.Println("Upgrade to MyProtocol!!")

	// 소켓 획득 : http.ResponseWriter를 하이재킹하여, 소켓을 통해 직접 통신
	// i.e http.ResponseWriter에서 데이터(헤더, 스테이터스 코드)를 전송하지 않음
	hijacker := w.(http.Hijacker)
	connect, readWriter, err := hijacker.Hijack()
	if err != nil {
		panic(err)
	}
	defer connect.Close()

	// 프로토콜이 바뀌었다는 응답 데이터 작성
	response := http.Response{
		StatusCode: 101,
		Header:     make(http.Header),
	}
	response.Header.Set("Upgrade", "MyProtocol")
	response.Header.Set("Connection", "Upgrade")
	response.Write(connect)

	// 소켓 통신
	for i := 1; i <= 10; i++ {
		// 클라이언트로 응답 작성 및 전송
		fmt.Fprintf(readWriter, "%d\n", i)
		fmt.Println("->(To Client)", i)
		readWriter.Flush()

		// 클라이언트 요청의 body에서 개행 문자를 기준으로 데이터를 읽어와 출력(<- 부분)
		recv, err := readWriter.ReadBytes('\n')
		if err == io.EOF {
			break
		}
		fmt.Printf("<-(From Client) %s", string(recv))
		time.Sleep(500 * time.Millisecond)
	}

}

func main() {
	var httpServer http.Server

	// 루트 경로에 handler 등록 : 루트 경로 접속 시, handler 함수 호출
	http.HandleFunc("/", handler)
	log.Println("start http listening: 18888")

	// 서버 포트 설정
	httpServer.Addr = ":18888"
	log.Println(httpServer.ListenAndServe())
}
