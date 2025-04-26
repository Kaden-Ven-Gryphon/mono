package clview

import (
	"fmt"
	"os"
	"os/exec"

	"github.com/kadengryphon/cw/pkg/cw"
)

func Console_Animate(b cw.CWboard, time int) {
	fmt.Println(b.String())
	for i := 0; i < time; i++ {
		cmd := exec.Command("cmd", "/c", "cls")
	    cmd.Stdout = os.Stdout
   		cmd.Run()
		b.Run(1)
		fmt.Println(b.String())

	}
}


func Print_details(b cw.CWboard) {
	fmt.Printf("Hight: %d\n", b.Hight)
	fmt.Printf("Width: %d\n", b.Width)
	fmt.Printf("Generation: %d\n", b.Generation)
}