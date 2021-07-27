// 서버 및 클라이언트에서 RCP 통신에 사용할 엔티티(데이터 구조체) 정의
package contract

type HelloWorldRequest struct {
	Name string
}

type HelloWorldResponse struct {
	Message string
}
