package main

import (
	"fmt"
	"log"
	"net/http"
	"sync"
	"time"

	"github.com/VividCortex/ewma"
)

var movingAverage ewma.MovingAverage
var threshold = 1000 * time.Millisecond
var timeout = 1000 * time.Millisecond
var resetting = false
var resetMutex = sync.RWMutex{} // 이동 평균을 위한 뮤텍스

func main() {
	movingAverage = ewma.NewMovingAverage()

	http.HandleFunc("/", mainHandler)
	http.HandleFunc("/health", healthCheckHandler)

	http.ListenAndServe(":8080", nil)
}

// 메인 요청 처리 핸들러
func mainHandler(w http.ResponseWriter, r *http.Request) {
	startTime := time.Now()

	// Healthy 상태가 아닌 경우 이동 평균 재계산
	if !isHealthy() {
		respondServiceUnhealthy(w)
		return
	}

	// 메인 요청 처리
	w.WriteHeader(http.StatusOK)
	fmt.Fprintf(w, "Average request time: %f (ms)\n", movingAverage.Value()/1000000)

	// 요청 처리 시간 update
	duration := time.Now().Sub(startTime)
	movingAverage.Add(float64(duration))
}

// 헬스 체크 핸들러
func healthCheckHandler(w http.ResponseWriter, r *http.Request) {
	if !isHealthy() {
		w.WriteHeader(http.StatusServiceUnavailable)
		return
	}

	fmt.Fprint(w, "OK")
}

// 이동 평균이 임계값보다 작은 경우만 Healthy 상태
func isHealthy() bool {
	return (movingAverage.Value() < float64(threshold))
}

func respondServiceUnhealthy(w http.ResponseWriter) {
	// 요청 처리 실패 헤더 추가
	w.WriteHeader(http.StatusServiceUnavailable)

	// 이동 평균 초기화를 위한 읽기 뮤텍스 고정
	resetMutex.RLock()
	defer resetMutex.RUnlock()

	if !resetting {
		go sleepAndResetAverage()
	}
}

// 이동 평균 초기화 : 초기화 보장을 위한 뮤텍스 사용
func sleepAndResetAverage() {
	resetMutex.Lock()
	resetting = true
	resetMutex.Unlock()

	// 과부하가 걸린 서비스가 원래 상태로 돌아오기를 기다리는 것
	log.Println("Waiting for service restoring....")
	time.Sleep(timeout)
	movingAverage = ewma.NewMovingAverage()

	resetMutex.Lock()
	resetting = false
	resetMutex.Unlock()
}
