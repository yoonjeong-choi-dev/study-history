package main

import (
	"fmt"
	"os"
	"path/filepath"
	"regexp"
)

func findIP(input string) string {
	// 네 개의 8비트 구성 요소 정의 : 0~255 사이의 숫자
	partIP := "(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])"

	// IPv4에 대한 정규 표현식 : 네 개의 8비트 정의
	grammar := partIP + "\\." + partIP + "\\." + partIP + "\\." + partIP

	// 정규표현식을 통해 일치하는 IPv4 검색
	matchMe := regexp.MustCompile(grammar)
	return matchMe.FindString(input)
}

func main() {
	args := os.Args
	if len(args) < 2 {
		fmt.Printf("usage: %s <string text>", filepath.Base(args[0]))
		os.Exit(-1)
	}

	var input string = ""
	for i := 0; i < len(args); i++ {
		input += args[i]
	}

	ip := findIP(input)

	if ip == "" {
		fmt.Println("No op")
	} else {
		fmt.Println("Your ip :", ip)
	}

}
