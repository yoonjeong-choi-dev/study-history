package main

import (
	"github.com/stretchr/testify/assert"
	"testing"
)

func TestSimpleSquare(t *testing.T) {
	rst := square(9)
	if rst != 81 {
		t.Errorf("square(9) should be 81 but square(9) return %d", rst)
	}
}

func TestSquare1(t *testing.T) {
	assert := assert.New(t)
	assert.Equal(81, square(9), "square(9) should be 81")
}

func TestSquare2(t *testing.T) {
	assert := assert.New(t)
	assert.Equal(9, square(3), "square(3) should be 9")
}
