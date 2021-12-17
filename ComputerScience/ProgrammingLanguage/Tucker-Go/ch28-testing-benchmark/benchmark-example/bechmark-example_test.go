package main

import (
	"github.com/stretchr/testify/assert"
	"testing"
)

func TestFibo1(t *testing.T) {
	assert := assert.New(t)

	assert.Equal(0, fibo1(-1), "fibo1(-1)")
	assert.Equal(0, fibo1(0), "fibo1(0)")
	assert.Equal(1, fibo1(1), "fibo1(1)")
	assert.Equal(2, fibo1(3), "fibo1(3)")
	assert.Equal(233, fibo1(13), "fibo1(13)")
}

func TestFibo2(t *testing.T) {
	assert := assert.New(t)

	assert.Equal(0, fibo2(-1), "fibo2(-1)")
	assert.Equal(0, fibo2(0), "fibo2(0)")
	assert.Equal(1, fibo2(1), "fibo2(1)")
	assert.Equal(2, fibo2(3), "fibo2(3)")
	assert.Equal(233, fibo2(13), "fibo2(13)")
}

func BenchmarkFibo1(b *testing.B) {
	for i := 0; i < b.N; i++ {
		fibo1(20)
	}
}

func BenchmarkFibo2(b *testing.B) {
	for i := 0; i < b.N; i++ {
		fibo2(20)
	}
}
