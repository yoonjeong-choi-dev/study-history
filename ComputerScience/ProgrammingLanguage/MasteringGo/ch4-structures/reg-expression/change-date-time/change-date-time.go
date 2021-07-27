package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"regexp"
	"strings"
	"time"
)

func main() {
	args := os.Args
	if len(args) == 1 {
		fmt.Println("Please provide one text file to process!")
		os.Exit(1)
	}

	filename := args[1]
	f, err := os.Open(filename)
	if err != nil {
		fmt.Printf("error opening file %s", err)
		os.Exit(1)
	}
	defer f.Close()

	notMatchPatterns := 0
	r := bufio.NewReader(f)
	for {
		line, err := r.ReadString('\n')
		if err == io.EOF {
			break
		} else if err != nil {
			fmt.Printf("error reading file %s", err)
		}

		// [DD/Month/YYYY:HH:MM:SS *] 형태 찾아서 변환
		r1 := regexp.MustCompile(`.*\[(\d\d\/\w+/\d\d\d\d:\d\d:\d\d:\d\d.*)\] .*`)
		if r1.MatchString(line) {
			match := r1.FindStringSubmatch(line)

			// time 자료형으로 변환 : time.Stamp 형식으로 변환하기 위해서 자료형변환 필요
			d1, err := time.Parse("02/Jan/2006:15:04:05 -0700", match[1])
			if err == nil {
				newFormat := d1.Format(time.Stamp)
				fmt.Print(strings.Replace(line, match[1], newFormat, 1))
			} else {
				notMatchPatterns++
			}
			continue
		}

		// [Month-DD-YY:HH:MM:SS *] 형태로 찾아서 변환
		r2 := regexp.MustCompile(`.*\[(\w+\-\d\d-\d\d:\d\d:\d\d:\d\d.*)\] .*`)
		if r2.MatchString(line) {
			match := r2.FindStringSubmatch(line)

			// time 자료형으로 변환 : time.Stamp 형식으로 변환하기 위해서 자료형변환 필요
			d1, err := time.Parse("Jan-02-06:15:04:05 -0700", match[1])
			if err == nil {
				newFormat := d1.Format(time.Stamp)
				fmt.Print(strings.Replace(line, match[1], newFormat, 1))
			} else {
				notMatchPatterns++
			}
		}
	}
	fmt.Println(notMatchPatterns, "lines did not match!")
}
