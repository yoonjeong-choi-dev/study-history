package main

import (
	"fmt"
	"math/rand"
	"net/url"
	"time"
)

/*
로드밸런싱 전략을 정의하는 인터페이스
- NextEndpoint : 전략에 맞는 특정 엔드포인트 리턴
- SetEndpoints : 현재 사용할 수 있는 엔드포인트 목록 지정
*/

type Strategy interface {
	NextEndpoint() url.URL
	SetEndpoints([]url.URL)
}

// 랜덤 전략 : 주어진 엔드포인트들 중에 랜덤으로 하나 선택
type RandomStrategy struct {
	endpoints []url.URL
}

// 랜덤으로 하나 선택
func (rs *RandomStrategy) NextEndpoint() url.URL {
	// 랜덤 숫자 생성
	s1 := rand.NewSource(time.Now().UnixNano())
	r1 := rand.New(s1)

	// 주어진 엔드포인트 리스트에서 하나 선택하여 반환
	return rs.endpoints[r1.Intn(len(rs.endpoints))]
}

func (r *RandomStrategy) SetEndpoints(endpoints []url.URL) {
	r.endpoints = endpoints
}

/*
로드밸런서 정의
- 로드밸런싱 전략 객체를 이용하여 로드밸런싱
- GetEndpoint : 전략을 이용하여 다음 엔드포인트 반환
- UpdateEndpoints : 인자로 받는 엔드포인트 리스트로 업데이트
*/
type LoadBalancer struct {
	strategy Strategy
}

func (l *LoadBalancer) GetEndpoint() url.URL {
	return l.strategy.NextEndpoint()
}

func (l *LoadBalancer) UpdateEndpoints(urls []url.URL) {
	l.strategy.SetEndpoints(urls)
}

// 로브밸런서 생성 함수
func NewLoadBalancer(strategy Strategy, endpoints []url.URL) *LoadBalancer {
	strategy.SetEndpoints(endpoints)
	return &LoadBalancer{strategy: strategy}
}

func main() {
	endpoints := []url.URL{
		url.URL{Host: "www.google.com"},
		url.URL{Host: "www.google.co.uk"},
		url.URL{Host: "www.google.co.kr"},
	}

	loadBalancer := NewLoadBalancer(&RandomStrategy{}, endpoints)

	for i := 0; i < 10; i++ {
		fmt.Printf("%d-test : ", i)
		fmt.Println(loadBalancer.GetEndpoint())
	}
}
