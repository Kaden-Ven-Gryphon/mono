# mono
Mono repository test ground for various small projects that might eventually grow into their own repository.

## C++

### Cipher Lib

A c++ library that has various different ciphers and cipher breaking methods.

### KecharaBot

A c++ based discord bot, I think it used the cipher lib to encode and decode text sent at it.

## C

### Hanoi

terminal based animation of tower of hanoi

### P10AI

My attempt to make a Phase 10 card game AI.  Most of the terminal based card game was functioning (shuffling the deck, drawing cards, playing hands) but still needed a bit more for varifing edge cases of valid hands.  Didn't get to start the AI part of it other than it counting cards to keep track of its current game state knowledge.

### TickTackToe

A generation/mutation based neural network that I tried to get to win at tic tac toe.  Never got great results, not sure if I never found a good way to give it a fitness score, or if some part of my neural network implementation was wrong.

### Ciphers

Simular to my C++ ciphers but in C

### kadenimg

png creator and image functions to create png visualization in C.  Can draw shapes, gradients, text, and transparency to png images.  Tried to make my own png file format read/write functions, but didn't finish.  Have most of the functionality to read blocks out of a png file, and a gzip function to decode but they were not working.  Was in the middle of decoding simple gzip compressed text by hand to compare to my functions and to a working python decompressor to figure it out.  Was making my own bitstream reader to clean it up.  Ran out of time and used a python script that convert the raw img binary to a png.

### pngGate

using the img lib and a graph based logic gate simulator to make animations of gate circuits running.  Was going to make a full cpu sim, but am planning to try it in rust with a different strategy insead this time.

## Go

### cwgolms

A kubernetes cluster that takes in a conway's game of life board start and returns what generation it halts, or loops on.

## Godot

### OpenVTube

A simple godot prototype that uses a opencv python server for face tracking and sends it to godot to display a vtuber, only uses the head position to lean following user movement.

## Python

### C mod Conway’s Soldier

A C lib that implement a text based conway's soldiers game and a python wrapper lib

### DKApp

The original dkapp project before I moved to making a tutorial and redoing the project from the ground up with the new knowledge I had gained.

### PythonBots

A collection of old python bots, that mostly just added the conway's soldiers game to discord

### Freecodecamp

certification projects

### kg_img

Convert images into dithered ascii text

### secret message

skill test project, pull google doc from url and pull text out of it then use table of coordinates from it to build ascii art secret message.

## Rust

### rouge test

following along the tutorial for using bracket lib https://bfnightly.bracketproductions.com/




