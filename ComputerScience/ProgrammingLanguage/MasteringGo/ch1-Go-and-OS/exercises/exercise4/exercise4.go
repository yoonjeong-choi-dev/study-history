package main

import (
	"fmt"
	"io"
	"log"
	"os"
)

var LOGFILE1 = "/tmp/exercise4_1.log"
var LOGFILE2 = "/tmp/exercise4_2.log"

func main() {
	// 644 권한을 가진 로그 파일 생성 or 접근
	logFile1, err := os.OpenFile(LOGFILE1, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println(err)
		return
	}
	defer logFile1.Close()

	logFile2, err := os.OpenFile(LOGFILE2, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println(err)
		return
	}
	defer logFile2.Close()

	// 해당 파일을 이용하여 로거 생성
	multiWriter := io.MultiWriter(os.Stdout, logFile1, logFile2)
	logger := log.New(multiWriter, "exercise4Logger", log.LstdFlags)

	// 로깅 방식 플래그 설정 : 로그 시간 및 로그 출력이 발생하는 소스코드 줄번호 출력
	logger.SetFlags(log.LstdFlags | log.Lshortfile)
	logger.Println("This is my custom logger!")
	logger.Println("Hello there~!")
}
