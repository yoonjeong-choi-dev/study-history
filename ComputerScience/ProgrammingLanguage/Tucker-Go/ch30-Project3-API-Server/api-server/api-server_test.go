package main

import (
	"encoding/json"
	"github.com/stretchr/testify/assert"
	"net/http"
	"net/http/httptest"
	"strings"
	"testing"
)

func TestGetListHandler(t *testing.T) {
	assert := assert.New(t)

	res := httptest.NewRecorder()
	req := httptest.NewRequest("GET", "/students", nil)

	mux := MakeWebHandler()
	mux.ServeHTTP(res, req)

	// 상태 코드 검증
	assert.Equal(http.StatusOK, res.Code)

	// 응답 바디 검증
	var list []Student
	err := json.NewDecoder(res.Body).Decode(&list)
	assert.Nil(err)
}

func TestGetStudentHandler(t *testing.T) {
	assert := assert.New(t)

	res := httptest.NewRecorder()
	req := httptest.NewRequest("GET", "/students/1", nil)

	mux := MakeWebHandler()
	mux.ServeHTTP(res, req)

	// 상태 코드 검증
	assert.Equal(http.StatusOK, res.Code)
}

func TestPostStudentHandler(t *testing.T) {
	assert := assert.New(t)

	res := httptest.NewRecorder()
	req := httptest.NewRequest("POST", "/students", strings.NewReader(`{"Id": 777, "Name":"New YJ", "Age": 30, "Score": 1000}`))
	//req := httptest.NewRequest("POST", "/students",strings.NewReader(`{"Id":0,"Name":"ccc","Age":15,"Score":78}`))

	mux := MakeWebHandler()
	mux.ServeHTTP(res, req)

	// 상태 코드 검증
	assert.Equal(http.StatusCreated, res.Code)

	// 추가된 학생 데이터 검증
	res = httptest.NewRecorder()
	req = httptest.NewRequest("GET", "/students/3", nil)
	mux.ServeHTTP(res, req)

	assert.Equal(http.StatusOK, res.Code)

	var student Student
	err := json.NewDecoder(res.Body).Decode(&student)
	assert.Nil(err)
	assert.Equal("New YJ", student.Name)
}

func TestDeleteStudentHandler(t *testing.T) {
	assert := assert.New(t)

	res := httptest.NewRecorder()
	req := httptest.NewRequest("DELETE", "/students/1", nil)

	mux := MakeWebHandler()
	mux.ServeHTTP(res, req)

	// 상태 코드 검증
	assert.Equal(http.StatusOK, res.Code)
}
