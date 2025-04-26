# Specify extensions of files to delete when cleaning
CLEANEXTS   = o a 

CC = gcc
CFLAGS = -Wall

# Specify the target file and the install directory
OUTPUTFILE  = libcipherslib.a
INSTALLDIR  = ../binaries

# Default target
.PHONY: all
all: $(OUTPUTFILE)

# Build libcwslib.a
$(OUTPUTFILE): vigenere.o
	ar r $@ $^
	ranlib $@

vigenere.o: vigenere.c vigenere.h
	$(CC) $(CFLAGS) -c vigenere.c


.PHONY: test
test:
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -o tester main.o -L. -lcipherslib


.PHONY: install
install:
	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)

.PHONY: clean 
clean:
	for file in $(CLEANEXTS); do rm -f *.$$file; done
	rm tester


