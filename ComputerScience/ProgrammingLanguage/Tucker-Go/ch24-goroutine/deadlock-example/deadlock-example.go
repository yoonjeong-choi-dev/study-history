package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

var wg sync.WaitGroup

func twoMutexDeadlock(name string, first, second *sync.Mutex, firstName, secondName string) {
	for i := 0; i < 100; i++ {
		fmt.Printf("%s starts to eat\n", name)

		// 첫번째 뮤텍스 접근
		first.Lock()
		fmt.Printf("%s get %s\n", name, firstName)

		// 두번째 뮤텍스 접근
		second.Lock()
		fmt.Printf("%s get %s\n", name, secondName)

		fmt.Printf("%s has eaten\n", name)
		time.Sleep(time.Duration(rand.Intn(1000)) * time.Millisecond)

		// 뮤텍스 잠금 해제
		second.Unlock()
		first.Unlock()
	}

	wg.Done()
}

func main() {
	rand.Seed(time.Now().UnixNano())

	wg.Add(2)

	fork := &sync.Mutex{}
	spoon := &sync.Mutex{}

	go twoMutexDeadlock("A", fork, spoon, "Fork", "Spoon")
	go twoMutexDeadlock("B", spoon, fork, "Spoon", "Fork")

	wg.Wait()
}
