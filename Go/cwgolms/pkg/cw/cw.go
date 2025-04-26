package cw

import (
	"bufio"
	"crypto/sha256"
	"errors"
	"io"
	"math/rand"
	"os"
	"slices"
	"strings"
)

// PUBLIC TYPES

type CWboard struct {
	// y,x y=row, x=colm
	Board []byte
	Width int
	Hight int
	Generation int
}

// PRIVATE CONSTS


var roofChar = byte('_')
var wallChar =  byte('|')
var deadChar =  byte('.')
var liveChar =  byte('#')


// PUBLIC METHODS

//unsafe
func (b *CWboard) Get(x,y int) byte {
	return b.Board[(x+1)+(y*(b.Width+2))]
}
func (b *CWboard) Set(x,y int, v byte) {
	b.Board[(x+1)+(y*(b.Width+2))] = v
}

// Init a board of size x, y and saves empty board to file
func Init_board_to_file(name string, x int, y int) string {
	fo, err := os.Create(name+".cwb")
	if err != nil {
		panic(err)
	}

	defer func() {
		if err := fo.Close(); err != nil {
			panic(err)
		}
	}()

	var s strings.Builder

	for i := 0; i < y; i++ {
		for j := 0; j < x; j++ {
			s.WriteString(".")
		}
		s.WriteString("\n")
	}

	if _, err := fo.Write([]byte(s.String())); err != nil {
		panic(err)
	}

	return name
}

// Init a board of size width, hight
func (b *CWboard) Init(width,hight int) {
	b.Board = slices.Repeat([]byte{0}, ((width+2)*(hight+2)))
	b.Hight = hight
	b.Width = width
}

func (b *CWboard) Rand() {
	
	for y := 0; y  < b.Hight; y++ {
		for x := 0; x < b.Width; x++ {
			r := rand.Intn(2)
			b.Set(x, y, byte(r))
		}
	}
}
// Read board from file and load it into b
func (b *CWboard) Load_board_from_file(name string) (err  error) {
	
	
	fi, err := os.Open(name+".cwb")
	if err != nil {
		return err
	}

	defer func() {
		closeErr := fi.Close()
		if err == nil {
			err = closeErr
		}
	}()

	x := -1
	y := 0
	r := bufio.NewReader(fi)
	for {
		buf, err := r.ReadBytes('\n')
		if err != nil && err != io.EOF {
			
			return err
		}
		if x == -1 {
			x = len(buf) - 1
			boardBuf := slices.Repeat([]byte{0}, x+2)
			b.Board = append(b.Board, boardBuf...)

		}
		if x == (len(buf)-1) {
			x = len(buf)-1
			row := sliceCharToBool(buf)
			row = slices.Insert(row, 0, 0)
			b.Board = append(b.Board, row...)

		} else if err != io.EOF{
			err = errors.New("invalid board format")
			return err
		}
		
		if err == io.EOF{
			err = nil
			break
		}
		y++
	}

	boardBuf := slices.Repeat([]byte{0}, x+2)
	b.Board = append(b.Board, boardBuf...)
	b.Hight = y
	b.Width = x
		
	return err
}

//updates the board by the given number of generations
func (b *CWboard) Run(generations int) {
		
	next := make([]byte, len(b.Board))

	for i := 0; i < generations; i++ {
		for y := b.Width+3; y < len(b.Board)-(b.Width+2); y+= b.Width+2 {
			for x := 0; x < b.Width; x++ {
				next[y+x] = b.cellNextState(x+y)
			}
			
		}
		b.Generation++
		b.Board = next
	}
}

// returns a string render of the board state
func (b *CWboard) String() string {
	var s strings.Builder

	s.WriteString(strings.Repeat(string(roofChar), b.Width+2))
	s.WriteByte('\n')
	for y := 1; y <= b.Hight; y++ {
		s.WriteByte(wallChar)	
		for x := 0; x <= b.Width; x++ {
			if b.Get(x,y) == 0 {
				s.WriteByte(deadChar)
			} else {
				s.WriteByte(liveChar)
			}
		}
		s.WriteByte(wallChar)
		s.WriteByte('\n')
	}

	s.WriteString(strings.Repeat(string(roofChar), b.Width+2))
	
	return s.String()
}

// Returns how many generations before the board dies or loops, or -1 if it hits n
func (b *CWboard) Stops(n int) (int, string) {
	
	var history []string
	var last string

	for i := 0; ; i++ {
		//extinct?
		if b.extinct() {
			return i, "Extinct"
		}
		
		//hash
		hashed := b.hash()

		if hashed == last {
			return i, "Static"
		}
		last = hashed

		//search histroy
		index, found := slices.BinarySearch(history, hashed)
		if found {
			return i, "Loop"
		}
		//insert into history
		history = slices.Insert(history, index, hashed)

		//update
		b.Run(1)

		if i > n {
			return -1, "Unknown"
		}
	}

}

// PRIVATE

// unsafe (does not check array bounds)
// returns 0 or 1 if cell at x,y should live next generation
func (b *CWboard) cellNextState(i int) (state byte) {

	sum := byte(0)
	sum += b.Board[(i-(b.Width+2))-1]
	sum += b.Board[(i-(b.Width+2))]
	sum += b.Board[(i-(b.Width+2))+1]
	sum += b.Board[i-1]
	sum += b.Board[i+1]
	sum += b.Board[(i+(b.Width+2))-1]
	sum += b.Board[(i+(b.Width+2))]
	sum += b.Board[(i+(b.Width+2))+1]



	if sum < 2 {
		state = 0
	} else if sum > 3 {
		state = 0
	} else if sum == 2 {
		state = b.Board[i]
	} else {
		state = 1
	}

	return state
}

// converts the saved file format to 0 and 1s
func sliceCharToBool( arr []byte) []byte {
	retVal := make([]byte, 0, len(arr))

	for _, c := range arr {
		if c == liveChar {
			retVal = append(retVal, 1)
		} else {
			retVal = append(retVal, 0)
		}
	}

	return retVal
}

func (b *CWboard) hash() string {
	h := sha256.New()
	h.Write(b.Board)
	return string(h.Sum(nil))
}

func (b *CWboard) extinct() bool {
	total := 0
	for i := 0; i < len(b.Board); i++ {
		total += int(b.Board[i])
	}
	return total == 0
}