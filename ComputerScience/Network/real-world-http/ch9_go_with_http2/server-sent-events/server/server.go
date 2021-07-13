package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"math/big"
	"net/http"
	"time"
)

var html []byte

// html을 브라우저로 송신
func handlerHTML(w http.ResponseWriter, r *http.Request) {
	w.Header().Add("Content-Type", "text/html")
	w.Write(html)
}

// 소수를 브라우저로 송신
func handlerPrimeSSE(w http.ResponseWriter, r *http.Request) {
	// 청크의 응용이므로 청크 사용을 위해 flusher로 캐스팅
	flusher, ok := w.(http.Flusher)
	if !ok {
		http.Error(w, "Streaming unsupported!", http.StatusInternalServerError)
		return
	}

	// 브라우저가 닫힐 때, CloseNotify 채널로 정보가 전송됨
	closeNotify := w.(http.CloseNotifier).CloseNotify()

	// header 정보 세팅
	w.Header().Set("Content-Type", "text/event-stream")
	w.Header().Set("Cache-Control", "no-cache")
	w.Header().Set("Connection", "keep-alive")
	w.Header().Set("Access-Control-Allow-Origin", "*")

	var num int64 = 1

	// 소수를 100개 구한다
	for id := 1; id <= 100; id++ {
		// 통신이 끊긴 경우(브라주어 종료)에 종료
		select {
		case <-closeNotify:
			log.Println("Connection closed from client")
			return
		default:
			// do nothing
		}

		// 확률론적으로 소수를 구한다
		for {
			num++
			if big.NewInt(num).ProbablyPrime(20) {
				log.Printf("%d is a prime", num)

				// 소수인 경우 응답데이터에 작성하여 클라이언트로 전송
				fmt.Fprintf(w, "data: {\"id\": %d, \"number\": %d}\n\n", id, num)
				flusher.Flush()
				time.Sleep(time.Second)
				break
			}
		}
	}

	// 100개 넘으면 송신 종료
	log.Println("Connection closed from Server")
}

func main() {
	var err error
	html, err = ioutil.ReadFile("index.html")
	if err != nil {
		panic(err)
	}

	http.HandleFunc("/", handlerHTML)
	http.HandleFunc("/prime", handlerPrimeSSE)

	log.Println("start http listening :18888")
	err = http.ListenAndServe(":18888", nil)
	log.Println(err)
}
