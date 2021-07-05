package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/md5"
	"crypto/rand"
	"crypto/rsa"
	"io"
	"testing"
)

// ----------------------- RSA : 공개 키 -----------------------
func prepareRSA() (sourceData, label []byte, privateKey *rsa.PrivateKey) {
	// 원본 데이터 생성
	sourceData = make([]byte, 128)
	io.ReadFull(rand.Reader, sourceData)

	// 빈 라벨 생성
	label = []byte("")

	// rsa 비밀 키 생성
	privateKey, _ = rsa.GenerateKey(rand.Reader, 2048)

	return
}

func BenchmarkRSAEncryption(b *testing.B) {
	// RSA 암호화 테스트에 필요한 리소스
	sourceData, label, privateKey := prepareRSA()

	// RSA 암호화에 필요한 리소스(공개키 및 해시 함수)
	publicKey := &privateKey.PublicKey
	md5hash := md5.New()

	// 암호화 성능 측정
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		rsa.EncryptOAEP(md5hash, rand.Reader, publicKey, sourceData, label)
	}
}

func BenchmarkRSADecryption(b *testing.B) {
	// RSA 복호화 테스트에 필요한 리소스
	sourceData, label, privateKey := prepareRSA()

	// RSA 암호호화에 필요한 리소스(공개키 및 해시 함수) 및 암호화
	publicKey := &privateKey.PublicKey
	md5hash := md5.New()
	encrypted, _ := rsa.EncryptOAEP(md5hash, rand.Reader, publicKey, sourceData, label)

	// 복호화 성능 측정
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		rsa.DecryptOAEP(md5hash, rand.Reader, privateKey, encrypted, label)
	}
}

// ----------------------- AES : 공통 키 -----------------------
func prepareAES() (sourceData, nounce []byte, gcm cipher.AEAD) {
	// 원본 데이터 랜덤 생성
	sourceData = make([]byte, 128)
	io.ReadFull(rand.Reader, sourceData)

	// 넌스값 랜덤 생성
	nounce = make([]byte, 12)
	io.ReadFull(rand.Reader, nounce)

	// 공통키 생성을 위한 키 랜덤 생성
	key := make([]byte, 32)
	io.ReadFull(rand.Reader, key)

	// 공통키 생성
	block, _ := aes.NewCipher(key)
	gcm, _ = cipher.NewGCM(block)

	return
}

func BenchmarkAESEncryption(b *testing.B) {
	// AES 암호화 테스트에 필요한 리소스
	sourceData, nounce, gcm := prepareAES()

	// 암호화 성능 측정
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		gcm.Seal(nil, nounce, sourceData, nil)
	}
}

func BenchmarkAESDecryption(b *testing.B) {
	// AES 암호화 테스트에 필요한 리소스
	sourceData, nounce, gcm := prepareAES()

	// AES 암호호화에 필요한 리소스(공개키 및 해시 함수) 및 암호화
	encrypted := gcm.Seal(nil, nounce, sourceData, nil)

	// 복호화 성능 측정
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		gcm.Open(nil, nounce, encrypted, nil)
	}
}
