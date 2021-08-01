package throttling

import "net/http"

// 처리할 핸들러(handler)를 랩핑하는 미들웨어
// 핸들러 호출 전 서버가 요청을 처리할 수 있는지 확인
type LimitHandler struct {
	connections chan struct{} // 버퍼링된 채널로의 연결 갯수
	handler     http.Handler  // 시스템이 정상인 경우 호출되는 핸들러
}

// LimitHanlder 생성 함수
func NewLimitHandler(connections int, next http.Handler) *LimitHandler {
	// connections : 한번에 처리할 수 있는 연결 갯수
	cons := make(chan struct{}, connections)
	for i := 0; i < connections; i++ {
		cons <- struct{}{}
	}

	return &LimitHandler{
		connections: cons,
		handler:     next,
	}
}

// 미들웨어 패턴 사용을 위해 Hander 인터페이스 구현체
func (lh *LimitHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	select {
	case <-lh.connections:
		// 채널에서 항목을 가져올 수 있는 경우 i.e 서버가 요청 처리 가능
		lh.handler.ServeHTTP(w, r)
		lh.connections <- struct{}{} // 잠금 해제
	default:
		// 서버가 정상이 아닌 경우
		http.Error(w, "Busy", http.StatusTooManyRequests)
	}
}
