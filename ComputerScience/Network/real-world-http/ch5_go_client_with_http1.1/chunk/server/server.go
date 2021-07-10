package main

import (
	"fmt"
	"log"
	"net/http"
	"net/http/httputil"
	"time"
)

func handler(writer http.ResponseWriter, req *http.Request) {
	dump, err := httputil.DumpRequest(req, true)
	if err != nil {
		http.Error(writer, fmt.Sprint(err), http.StatusInternalServerError)
		return
	}
	fmt.Println(string(dump))
	fmt.Fprintf(writer, "<html><body>hello</body></html>\n")
}

func handlerChunckedReponse(w http.ResponseWriter, r *http.Request) {
	// ResponseWriter 인터페이스를 Flusher 인터페이스로 캐스팅하여 청크 형식 전송
	flusher, ok := w.(http.Flusher)
	if !ok {
		panic("expected http.ResponseWriter to be an http.Flusher")
	}

	// 10개의 데이터를 청크하여 클라이언트에 전송
	for i := 1; i <= 10; i++ {
		fmt.Fprintf(w, "Chunk #%d\n", i)
		log.Printf("Chunk #%d\n", i)

		// Flush 메서드를 통해 각 루프 문마다 청크 전송
		flusher.Flush()
		time.Sleep(500 * time.Millisecond)
	}
	flusher.Flush()
}

func main() {
	var httpServer http.Server

	// handler 등록
	http.HandleFunc("/", handler)
	http.HandleFunc("/chunked", handlerChunckedReponse)
	log.Println("start http listening: 18888")

	// 서버 포트 설정
	httpServer.Addr = ":18888"
	log.Println(httpServer.ListenAndServe())
}
