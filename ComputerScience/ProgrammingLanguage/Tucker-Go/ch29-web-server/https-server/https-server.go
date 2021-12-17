package main

import (
	"io/ioutil"
	"log"
	"net/http"
)

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

func main() {
	mux := http.NewServeMux()

	// File Server
	mux.Handle("/static/", http.StripPrefix("/static/", http.FileServer(http.Dir("static"))))
	mux.HandleFunc("/", indexHandler)

	// HTTPS listen : 공개키 및 비밀키 설정
	err := http.ListenAndServeTLS(":8080", "./cert/localhost.crt", "./cert/localhost.key", mux)
	if err != nil {
		log.Fatal(err)
	}
}
