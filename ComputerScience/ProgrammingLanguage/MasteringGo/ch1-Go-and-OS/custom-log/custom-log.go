package main

import (
	"fmt"
	"log"
	"os"
)

// /temp 디렉터리는 재부팅시 데이터가 삭제되고, 루트 권한이 필요 없음
var LOGFILE = "/tmp/myGoLog.log"

func main() {
	// 644 권한을 가진 로그 파일 생성 or 접근
	logFile, err := os.OpenFile(LOGFILE, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Println(err)
		return
	}

	defer logFile.Close()

	// 해당 파일을 이용하여 로거 생성
	logger := log.New(logFile, "customLog", log.LstdFlags)

	// 로깅 방식 플래그 설정 : 로그 시간 및 로그 출력이 발생하는 소스코드 줄번호 출력
	logger.SetFlags(log.LstdFlags | log.Lshortfile)
	logger.Println("This is my custom logger!")
	logger.Println("Hello there~!")

}
