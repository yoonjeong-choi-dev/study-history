package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"strconv"
)

type Student struct {
	Name  string
	Age   int
	Score int
}

func studentHandler(w http.ResponseWriter, r *http.Request) {
	var s = Student{"Yoonjeong", 29, 77}
	data, _ := json.Marshal(s)

	w.Header().Add("content-type", "application/json")
	w.WriteHeader(http.StatusOK)
	fmt.Fprint(w, string(data))
}

func indexHandler(w http.ResponseWriter, r *http.Request) {
	localPath := "static/index.html"
	content, err := ioutil.ReadFile(localPath)
	if err != nil {
		w.WriteHeader(404)
		w.Write([]byte(http.StatusText(404)))
		return
	}

	w.Write(content)
}

func greetHandler(w http.ResponseWriter, r *http.Request) {
	query := r.URL.Query()
	name := query.Get("name")
	if name == "" {
		name = "anonymous"
	}
	id, err := strconv.Atoi(query.Get("id"))
	if err != nil {
		fmt.Fprintf(w, "Hello %s! I don't know your id..", name)
	} else {
		fmt.Fprintf(w, "Hello %s! Your id is %d", name, id)
	}
}

func MakeWebHandler() http.Handler {
	mux := http.NewServeMux()

	// File Server
	mux.Handle("/static/", http.StripPrefix("/static/", http.FileServer(http.Dir("static"))))

	mux.HandleFunc("/greet", greetHandler)
	mux.HandleFunc("/student", studentHandler)
	mux.HandleFunc("/", indexHandler)

	return mux
}

func main() {
	log.Println(http.ListenAndServe(":8080", MakeWebHandler()))
}
