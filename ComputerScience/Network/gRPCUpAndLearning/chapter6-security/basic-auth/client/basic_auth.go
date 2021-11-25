package main

import (
	"context"
	"encoding/base64"
)

// 커스텀 자격 증명을 위한 구조체 : PerRPCCredential 인터페이스
type BasicAuth struct {
	username string
	password string
}

func (b BasicAuth) GetRequestMetadata(ctx context.Context, in ...string) (map[string]string, error) {
	// Authorization 헤더에 포함시켜야 하는 문자열
	auth := b.username + ":" + b.password

	// base64 인코딩 및 메타데이터 반환
	enc := base64.StdEncoding.EncodeToString([]byte(auth))
	return map[string]string{
		"authorization": "Basic " + enc,
	}, nil
}

// 사용자명 및 비밀번호 암호화를 위한 채널 보안 설정
func (b BasicAuth) RequireTransportSecurity() bool {
	return true
}
