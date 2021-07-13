package main

import (
	"bufio"
	"bytes"
	"context"
	"fmt"
	"io"
	"net/http"
	"os"
)

type Event struct {
	Name string
	ID   string
	Data string
}

// 인자로 받은 url로 http 연결
func EventSource(url string) (chan Event, context.Context, error) {
	reqeust, err := http.NewRequest("GET", url, nil)
	if err != nil {
		return nil, nil, err
	}

	response, err := http.DefaultClient.Do(reqeust)
	if err != nil {
		return nil, nil, err
	}

	if response.StatusCode != 200 {
		return nil, nil, fmt.Errorf("Response Status Code shoud be 200, but %d\n", response.StatusCode)
	}

	ctx, cancel := context.WithCancel(reqeust.Context())
	events := make(chan Event)
	go receiveSSE(events, cancel, response)
	return events, ctx, nil
}

// sever-sent event 파싱 : 서버에서 오는 데이터는 줄바꿈이 구분문자임
// 파싱 처리 결과를 Event 구조체에 넣어 채널로 보낸다
func receiveSSE(events chan Event, cancel context.CancelFunc, res *http.Response) {
	reader := bufio.NewReader(res.Body)
	var buffer bytes.Buffer
	event := Event{}

	for {
		// 서버에서 오는 데이터는 줄바꿈이 구분문자임
		line, err := reader.ReadBytes('\n')
		if err != nil {
			close(events)
			if err == io.EOF {
				cancel()
				return
			} else {
				panic(err)
			}
		}
		fmt.Println("TEST:", string(line[:]))
		// 파싱
		switch {
		case bytes.HasPrefix(line, []byte(":ok")):
			// skip
		case bytes.HasPrefix(line, []byte("id:")):
			event.ID = string(line[4 : len(line)-1])
		case bytes.HasPrefix(line, []byte("event:")):
			event.Name = string(line[7 : len(line)-1])
		case bytes.HasPrefix(line, []byte("data:")):
			buffer.Write(line[6:])
		case bytes.Equal(line, []byte("\n")):
			event.Data = buffer.String()
			buffer.Reset()
			if event.Data != "" {
				events <- event
			}
		default:
			fmt.Fprintf(os.Stderr, "Parse Error : %s\n", line)
			cancel()
			close(events)
		}
	}
}

func main() {
	events, ctx, err := EventSource("http://localhost:18888/prime")
	if err != nil {
		panic(err)
	}

	for {
		select {
		case <-ctx.Done():
			return
		case event := <-events:
			fmt.Printf("Event(Id=%s, Name=%s): %s\n", event.ID, event.Name, event.Data)
		}
	}
}
