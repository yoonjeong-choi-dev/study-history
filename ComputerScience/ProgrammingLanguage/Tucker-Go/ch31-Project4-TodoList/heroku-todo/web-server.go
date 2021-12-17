package main

import (
	"encoding/json"
	"log"
	"net/http"
	"os"
	"sort"
	"strconv"

	"github.com/gorilla/mux"
	"github.com/unrolled/render"
	"github.com/urfave/negroni"
)

// 응답 포멧터 정의
var rd *render.Render

// Todo 구조체 정의 (json 포멧도 정의)
type Todo struct {
	ID        int    `json:"id,omitempty"`
	Name      string `json:"name"`
	Completed bool   `json:"completed,omitempty"`
}

// ID로 정렬을 하기 위한 인터페이스 정의
type Todos []Todo

func (t Todos) Len() int {
	return len(t)
}
func (t Todos) Swap(i, j int) {
	t[i], t[j] = t[j], t[i]
}
func (t Todos) Less(i, j int) bool {
	return t[i].ID > t[j].ID
}

// 성공/실패 응답용 구조체 정의
type SuccessResponse struct {
	Success bool `json:"success"`
}

// 인메모리 DB
var todoMap map[int]Todo
var lastID int = 0

func MakeWebHandler() http.Handler {
	todoMap = make(map[int]Todo)

	mux := mux.NewRouter()
	mux.Handle("/", http.FileServer(http.Dir("public")))
	mux.HandleFunc("/todos", GetTodoListHandler).Methods("GET")
	mux.HandleFunc("/todos", PostTodoHandler).Methods("POST")
	mux.HandleFunc("/todos/{id:[0-9]+}", PutTodoHandler).Methods("PUT")
	mux.HandleFunc("/todos/{id:[0-9]+}", DeleteTodoHandler).Methods("DELETE")

	return mux
}

// 핸들러 정의
func GetTodoListHandler(w http.ResponseWriter, r *http.Request) {
	list := make(Todos, 0)
	for _, todo := range todoMap {
		list = append(list, todo)
	}

	sort.Sort(list)
	rd.JSON(w, http.StatusOK, list)
}

func PostTodoHandler(w http.ResponseWriter, r *http.Request) {
	var todo Todo
	err := json.NewDecoder(r.Body).Decode(&todo)
	if err != nil {
		log.Fatal(err)
		w.WriteHeader(http.StatusBadRequest)
		return
	}

	lastID++
	todo.ID = lastID
	todoMap[lastID] = todo
	rd.JSON(w, http.StatusCreated, todo)
}

func PutTodoHandler(w http.ResponseWriter, r *http.Request) {
	var reqTodo Todo
	err := json.NewDecoder(r.Body).Decode(&reqTodo)
	if err != nil {
		log.Fatal(err)
		w.WriteHeader(http.StatusBadRequest)
		return
	}

	vars := mux.Vars(r)
	id, _ := strconv.Atoi(vars["id"])
	if _, ok := todoMap[id]; ok {
		reqTodo.ID = id
		todoMap[id] = reqTodo

		rd.JSON(w, http.StatusOK, SuccessResponse{true})
	} else {
		rd.JSON(w, http.StatusNotFound, SuccessResponse{false})
	}
}

func DeleteTodoHandler(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	id, _ := strconv.Atoi(vars["id"])
	if _, ok := todoMap[id]; ok {
		delete(todoMap, id)
		rd.JSON(w, http.StatusOK, SuccessResponse{true})
	} else {
		rd.JSON(w, http.StatusNotFound, SuccessResponse{false})
	}
}

func main() {
	rd = render.New()

	handler := MakeWebHandler()

	// 로그, 복구 기능 및 파일 서버 기능을 지원하는 클래식 핸들러 생성 및 등록
	negroniHandler := negroni.Classic()
	negroniHandler.UseHandler(handler)

	// 환경변수에서 포트 가져오기
	log.Println("Started App")
	port := os.Getenv("PORT")
	err := http.ListenAndServe(":"+port, negroniHandler)
	if err != nil {
		panic(err)
	}
}
