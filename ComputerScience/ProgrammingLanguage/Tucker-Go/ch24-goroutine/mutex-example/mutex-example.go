package main

import (
	"fmt"
	"sync"
	"time"
)

var wg sync.WaitGroup

// 각 고루틴이 사용할 뮤텍스
var mutex sync.Mutex

type Account struct {
	Balance int
}

func DepositeAndWithdraw(account *Account) {
	defer wg.Done()

	// 뮤텍스 획득 및 함수 실행 완료 후 반납
	mutex.Lock()
	defer mutex.Unlock()

	if account.Balance < 0 {
		panic(fmt.Sprintf("Balance must be non-negative : %d", account.Balance))
	}

	fmt.Println("Deposite....")
	account.Balance += 1000

	time.Sleep(time.Millisecond)

	fmt.Println("Withdraw....")
	account.Balance -= 1000
}

func main() {
	account := &Account{0}

	wg.Add(10)
	for i := 0; i < 10; i++ {
		go DepositeAndWithdraw(account)
	}

	wg.Wait()
}
