package main

import (
	"fmt"
	"sync"
	"time"
)

var mutex = &sync.Mutex{}

func changeMap(myMap map[int]int, curStep int) {
	mutex.Lock()
	fmt.Printf("[%d] Prev: %d\n", curStep, myMap[0])
	myMap[0] = curStep
	mutex.Unlock()
}

func main() {
	var myMap = make(map[int]int)
	myMap[0] = 0

	for i := 1; i < 11; i++ {
		go changeMap(myMap, i)
	}

	time.Sleep(time.Second)
}
