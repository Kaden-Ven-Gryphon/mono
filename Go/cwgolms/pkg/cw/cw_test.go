package cw

import (
	"testing"
)

func TestCWStop1 (t *testing.T) {
	var b CWboard
	b.Init(10,10)
	b.Set(3,3,1)
	b.Set(4,3,1)
	b.Set(5,3,1)
	n, s := b.Stops(100)
	wantN := 2
	wantS := "Loop"
	if n != wantN || s != wantS {
		t.Fatalf("n = %d, expected %d.  s = %s, expected %s", n, wantN, s, wantS)
	}
}

func TestCWStop2 (t* testing.T) {
	var b CWboard
	b.Init(10,10)
	b.Set(3,3,1)
	b.Set(4,3,1)
	b.Set(3,4,1)
	b.Set(4,4,1)
	n, s := b.Stops(100)
	wantN := 1
	wantS := "Static"
	if n != wantN || s != wantS {
		t.Fatalf("n = %d, expected %d.  s = %s, expected %s", n, wantN, s, wantS)
	}
}


func TestCWStop3 (t* testing.T) {
	var b CWboard
	b.Init(10,10)
	b.Set(3,3,1)
	b.Set(4,3,1)
	b.Set(5,3,1)
	b.Set(6,3,1)
	b.Set(7,3,1)
	n, s := b.Stops(100)
	wantN := 27
	wantS := "Extinct"
	if n != wantN || s != wantS {
		t.Fatalf("n = %d, expected %d.  s = %s, expected %s", n, wantN, s, wantS)
	}
}
