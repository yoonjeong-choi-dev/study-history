package main

import (
	"bufio"
	"fmt"
	"os"
	"path/filepath"
	"strings"
)

type LineInfo struct {
	lineNo int
	line   string
}

type FindInfo struct {
	filname string
	lines   []LineInfo
}

func main() {

	if len(os.Args) < 3 {
		fmt.Printf("[usage] %s <word> <filepath> [<filepath2> ..]\n", os.Args[0])
		os.Exit(-1)
	}

	word := os.Args[1]
	files := os.Args[2:]
	findInfos := []FindInfo{}

	// 각 파일 경로 인자에 대해서 검색 수행
	for _, path := range files {
		findInfos = append(findInfos, FindWordInAllFiles(word, path)...)
	}

	// 결과 출력
	for _, findInfo := range findInfos {
		fmt.Println("==============================")

		fmt.Println(findInfo.filname)
		for _, lineInfo := range findInfo.lines {
			fmt.Println("\t", lineInfo.lineNo, "\t", lineInfo.line)
		}

		fmt.Println("==============================")
		fmt.Println()
	}
}

func GetFileList(path string) ([]string, error) {
	return filepath.Glob(path)
}

func FindWordInAllFiles(word, path string) []FindInfo {
	findInfos := []FindInfo{}

	files, err := GetFileList(path)
	if err != nil {
		fmt.Println("Cannot find the files. Error :", err)
		os.Exit(-1)
	}

	// 각 파일에 대해서 고루틴을 이용하여 검색 병렬 처리
	ch := make(chan FindInfo)
	numfiles := len(files)
	recvCount := 0

	for _, filename := range files {
		go FindWordInFile(word, filename, ch)
	}

	// 결과 수집
	for findInfo := range ch {
		findInfos = append(findInfos, findInfo)

		// 종료 시점 계산
		recvCount++
		if numfiles == recvCount {
			break
		}
	}

	return findInfos
}

// 채널을 통해 검색 결과 전달
func FindWordInFile(word, filename string, ch chan FindInfo) {
	findInfo := FindInfo{filname: filename, lines: []LineInfo{}}

	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Cannot open the file :", filename)
		os.Exit(-1)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	lineNo := 1
	for scanner.Scan() {
		line := scanner.Text()

		// 단어가 포함된 경우 추가
		if strings.Contains(line, word) {
			findInfo.lines = append(findInfo.lines, LineInfo{lineNo, line})
		}
		lineNo++
	}

	// 결과 전송
	ch <- findInfo
}
