package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

func main() {
	args := os.Args
	if len(args) < 2 {
		fmt.Printf("Usage : select-column.go column-number <file1> [<file2> [...<fileN>]]\n")
		os.Exit(1)
	}

	temp, err := strconv.Atoi(args[1])
	if err != nil {
		fmt.Println("column-number must be an integer :", temp)
		os.Exit(1)
	}

	column := temp
	if column < 0 {
		fmt.Println("Invalid column number :", column)
		os.Exit(1)
	}

	for _, filename := range args[2:] {
		fmt.Println("\t\t", filename)
		f, err := os.Open(filename)
		if err != nil {
			fmt.Printf("error to open file %s\n", filename)
			os.Exit(1)
		}
		defer f.Close()

		r := bufio.NewReader(f)
		for {
			line, err := r.ReadString('\n')
			if err == io.EOF {
				break
			} else if err != nil {
				fmt.Printf("error reading file %s", err)
			}

			// bufio는 파일을 읽어 바이트 슬라이스로 반환 => 문자열 변환 필요
			// Fields : 공백 문자를 기준으로 각 라인을 나누어 준다
			data := strings.Fields(line)
			if len(data) >= column {
				fmt.Println((data[column-1]))
			}
		}
	}
}
