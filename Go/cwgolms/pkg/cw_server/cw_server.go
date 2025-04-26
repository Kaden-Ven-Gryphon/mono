package cw_server

import (
	"encoding/json"
	"log"
	"net/http"
	"strconv"

	"github.com/Kaden-Ven-Gryphon/cwgolms/pkg/cw"
)

type CWServer struct {
}

func New() *CWServer {
	s := CWServer{}
	return &s
}

func (cs *CWServer) InitBoardHandler(w http.ResponseWriter, req *http.Request) {
	log.Printf("Handling get task at %s/n", req.URL.Path)

	width, err := strconv.Atoi(req.PathValue("width"))
	if err != nil {
		http.Error(w, "invalid width", http.StatusBadRequest)
		return
	}

	hight, err := strconv.Atoi(req.PathValue("hight"))
	if err != nil {
		http.Error(w, "invalid hight", http.StatusBadRequest)
	}

	var board cw.CWboard
	board.Init(width, hight)

	js, err := json.Marshal(board)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	w.Header().Set("Content-Type", "application/json")
	w.Write(js)
}

func (cs *CWServer) RandHandler(w http.ResponseWriter, req *http.Request) {
	width, err := strconv.Atoi(req.PathValue("width"))
	if err != nil {
		http.Error(w, "invalid width", http.StatusBadRequest)
		return
	}

	hight, err := strconv.Atoi(req.PathValue("hight"))
	if err != nil {
		http.Error(w, "invalid hight", http.StatusBadRequest)
	}

	var board cw.CWboard
	board.Init(width, hight)
	board.Rand()

	js, err := json.Marshal(board)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	w.Header().Set("Content-Type", "application/json")
	w.Write(js)
}

type returnStruct struct {
	N int
	S string
}

func (cs *CWServer) StopsHandler(w http.ResponseWriter, req *http.Request) {
	var b cw.CWboard

	err := json.NewDecoder(req.Body).Decode(&b)
	if err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	n, s := b.Stops(1000)

	ret := returnStruct{n,s}


	js, err := json.Marshal(ret)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	w.Header().Set("Content-Type", "application/json")
	w.Write(js)
}