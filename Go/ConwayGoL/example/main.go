package main

import (
	"fmt"

	"github.com/kadengryphon/cw/pkg/cw"
	"github.com/kadengryphon/cw/pkg/cw/clview"
)

func main() {
	fmt.Println("Init board")
	//cw.Init_board_to_file("test", 50, 50)
	var b cw.CWboard
	b.Init(20,20)
	b.Rand()
	copy := b
	count, code := b.Stops(1000)
	clview.Console_Animate(copy, 1000)
	fmt.Printf("Count: %d, Code: %s\n", count, code)
	
}

