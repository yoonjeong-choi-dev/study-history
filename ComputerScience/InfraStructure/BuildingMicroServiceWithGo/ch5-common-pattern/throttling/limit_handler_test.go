package throttling

import (
	"context"
	"net/http"
	"net/http/httptest"
	"sync"
	"testing"
	"time"

	"github.com/stretchr/testify/assert"
)

// 테스트 핸들러 생성 : LimitHanlder가 감싸는 메인 핸들러
func newTestHandler(ctx context.Context) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.WriteHeader(http.StatusOK)

		// 컨텍스트의 done 채널에 항목이 있을 때까지 대기 : 서버 요청이 수락될 때까지 대기
		<-r.Context().Done()
	})
}

// 테스트용 요청 생성
func setup(ctx context.Context) (*httptest.ResponseRecorder, *http.Request) {
	r := httptest.NewRequest("GET", "/health", nil)
	r = r.WithContext(ctx)
	return httptest.NewRecorder(), r
}

// 0 개의 채널에 대한 테스트
func TestReturnsBusyWhen0Connections(t *testing.T) {
	// 테스트를 위한 컨텍스트 및 핸들러, 요청 생성
	ctx, cancel := context.WithCancel(context.Background())
	w, r := setup(ctx)

	// 0 개의 채널을 가지는 핸들러 생성
	handler := NewLimitHandler(0, newTestHandler(ctx))

	time.AfterFunc(10*time.Millisecond, func() {
		cancel()
	})
	handler.ServeHTTP(w, r)

	// 채널이 0개이기 때문에 임계치 초과로 실패
	assert.Equal(t, http.StatusTooManyRequests, w.Code)
}

// 2개의 채널에 대한 2개의 동시 요청
func TestReturnsOKWith2ConnnectionsAndConnectionLimit2(t *testing.T) {
	// 동시 요청을 위한 2개의 컨텍스트와 요청 생성
	ctx, cancel := context.WithCancel(context.Background())
	ctx2, cancel2 := context.WithCancel(context.Background())
	w, r := setup(ctx)
	w2, r2 := setup(ctx2)

	// 2개의 채널을 가지는 핸들러 생성
	handler := NewLimitHandler(2, newTestHandler(ctx))

	time.AfterFunc(10*time.Millisecond, func() {
		cancel()
		cancel2()
	})

	waitGroup := sync.WaitGroup{}
	waitGroup.Add(2)

	go func() {
		handler.ServeHTTP(w, r)
		waitGroup.Done()
	}()

	go func() {
		handler.ServeHTTP(w2, r2)
		waitGroup.Done()
	}()

	waitGroup.Wait()

	// 임계치 내에서 동시 요청을 했기 때문에 성공
	if w.Code != http.StatusOK && w2.Code != http.StatusOK {
		t.Fatalf("Both requests should be OK, request 1: %v, request 2: %v", w.Code, w2.Code)
	}
}

// 1개의 채널에 대한 2개의 동시 요청 => 임계치 초과로 실패
func TestReturnsBusyWhenConnectionsExhausted(t *testing.T) {
	// 동시 요청을 위한 2개의 컨텍스트와 요청 생성
	ctx, cancel := context.WithCancel(context.Background())
	ctx2, cancel2 := context.WithCancel(context.Background())
	w, r := setup(ctx)
	w2, r2 := setup(ctx2)

	// 1개의 채널을 가지는 핸들러 생성
	handler := NewLimitHandler(1, newTestHandler(ctx))

	// 테스트가 완료할 수 있도록 10밀리초 대기
	time.AfterFunc(10*time.Millisecond, func() {
		cancel()
		cancel2()
	})

	// Go 루틴에서 핸들러 호출을 완료할 때까지 대기하기 위한 코드
	// => 테스트를 위한 고루틴이 끝난 후에, 결과 검증이 가능
	waitGroup := sync.WaitGroup{}
	waitGroup.Add(2)

	go func() {
		handler.ServeHTTP(w, r)
		waitGroup.Done()
	}()

	go func() {
		handler.ServeHTTP(w2, r2)
		waitGroup.Done()
	}()

	waitGroup.Wait()

	// 임계값 초과로 인해 두 개의 요청이 모두 성공 불가능
	if w.Code == http.StatusOK && w2.Code == http.StatusOK {
		t.Fatalf("One request should have been busy, request 1: %v, request 2: %v", w.Code, w2.Code)
	}
}

// 2개의 요청이 순차적으로 진행
func TestReleasesConnectionLockWhenFinished(t *testing.T) {
	// 요청을 위한 2개의 컨텍스트와 요청 생성
	ctx, cancel := context.WithCancel(context.Background())
	ctx2, cancel2 := context.WithCancel(context.Background())
	w, r := setup(ctx)
	w2, r2 := setup(ctx2)

	// 1개의 채널을 가지는 핸들러 생성
	handler := NewLimitHandler(1, newTestHandler(ctx))

	cancel()
	cancel2()

	waitGroup := sync.WaitGroup{}
	waitGroup.Add(2)

	// 2개의 요청이 순차적으로 진행
	go func() {
		handler.ServeHTTP(w, r)
		waitGroup.Done()
		handler.ServeHTTP(w2, r2)
		waitGroup.Done()
	}()

	waitGroup.Wait()

	// 순차적으로 진행하기 때문에 두 요청 모두 성공적으로 처리되어야 함
	if w.Code != http.StatusOK || w2.Code != http.StatusOK {
		t.Fatalf("One request should have been busy, request 1: %v, request 2: %v", w.Code, w2.Code)
	}
}
