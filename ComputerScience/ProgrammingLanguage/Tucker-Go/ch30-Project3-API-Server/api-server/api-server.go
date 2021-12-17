package main

import (
	"encoding/json"
	"log"
	"net/http"
	"sort"
	"strconv"

	"github.com/gorilla/mux"
)

type Student struct {
	Id    int
	Name  string
	Age   int
	Score int
}

// ID로 정렬하는 인터페이스
type Students []Student

func (s Students) Len() int {
	return len(s)
}
func (s Students) Swap(i, j int) {
	s[i], s[j] = s[j], s[i]
}
func (s Students) Less(i, j int) bool {
	return s[i].Id < s[j].Id
}

// 인메모리 DB
var students map[int]Student
var lastId int

// 다양한 핸들러 구현
func GetStudentsListHandler(w http.ResponseWriter, r *http.Request) {
	// 모든 학생 데이터 리스트로 반환
	list := make(Students, 0)
	for _, student := range students {
		list = append(list, student)
	}

	// ID를 이용하여 정렬
	sort.Sort(list)

	// 응답 작성
	w.WriteHeader(http.StatusOK)
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(list)
}

func GetStudentHandler(w http.ResponseWriter, r *http.Request) {
	// 쿼리 파라미터 가져오기
	vars := mux.Vars(r)
	id, _ := strconv.Atoi(vars["id"])

	student, ok := students[id]
	if !ok {
		w.WriteHeader(http.StatusNotFound)
		return
	}

	w.WriteHeader(http.StatusOK)
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(student)
}

func PostStudentHandler(w http.ResponseWriter, r *http.Request) {
	var student Student
	err := json.NewDecoder(r.Body).Decode(&student)

	if err != nil {
		log.Println(student)
		w.WriteHeader(http.StatusBadRequest)
		return
	}

	lastId++
	student.Id = lastId
	students[lastId] = student
	w.WriteHeader(http.StatusCreated)
}

func DeleteStudentHandler(w http.ResponseWriter, r *http.Request) {
	// 쿼리 파라미터 가져오기
	vars := mux.Vars(r)
	id, _ := strconv.Atoi(vars["id"])

	_, ok := students[id]
	if !ok {
		w.WriteHeader(http.StatusNotFound)
		return
	}

	delete(students, id)
	w.WriteHeader(http.StatusOK)
}

// 핸들러 등록
func MakeWebHandler() http.Handler {
	// 임시 데이터 생성
	students = make(map[int]Student)
	students[1] = Student{1, "YJ", 29, 77}
	students[2] = Student{2, "Yoonjeong", 30, 100}
	lastId = 2

	// gorilla/mux를 이용한 라우터 생성
	mux := mux.NewRouter()

	// 핸들러 등록
	mux.HandleFunc("/students", GetStudentsListHandler).Methods("GET")
	mux.HandleFunc("/students/{id:[0-9]+}", GetStudentHandler).Methods("GET")
	mux.HandleFunc("/students", PostStudentHandler).Methods("POST")
	mux.HandleFunc("/students/{id:[0-9]+}", DeleteStudentHandler).Methods("DELETE")

	return mux
}

func main() {

	// 서버 오픈
	http.ListenAndServe(":8080", MakeWebHandler())
}
