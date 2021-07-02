package main

import (
	"fmt"
	"log"
	"log/syslog"
	"os"
	"path/filepath"
)

func checkErr(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func main() {
	programName := filepath.Base(os.Args[0])

	// INFO 수준의 로그를 사용자 정의 로그(local7)에 저장 : /var/log/syslog 확인
	sysLog, err := syslog.New(syslog.LOG_INFO|syslog.LOG_LOCAL7, programName)
	checkErr(err)
	log.SetOutput(sysLog)
	log.Println("LOG_INFO + LOG_LOCAL 7 : Logging in GO!")
	fmt.Println("Check /var/log/syslog")

	// 로그 종류가 mail인 로그 저장 : /var/log/mail.log 확인
	sysLog, err = syslog.New(syslog.LOG_MAIL, programName)
	checkErr(err)
	log.SetOutput(sysLog)
	log.Println("LOG_MAIL : Logging in GO!")
	fmt.Println("Check /var/log/mail.log")
}
