package main

import (
	"log"
	"net/http"

	"github.com/Kaden-Ven-Gryphon/cwgolms/pkg/cw_server"
)


func main() {
	mux := http.NewServeMux()
	//Interface for the cgol functions
	server := cw_server.New()

	//get an empty board
	mux.HandleFunc("GET /init/{width}/{hight}/", server.InitBoardHandler)

	//get a randomized board
	mux.HandleFunc("GET /rand/{width}/{hight}/", server.RandHandler)

	//check if the board extincts, frezes, loops, within the next 1000 generations
	mux.HandleFunc("POST /stops/", server.StopsHandler)

	log.Fatal(http.ListenAndServe(":8080", mux))
}