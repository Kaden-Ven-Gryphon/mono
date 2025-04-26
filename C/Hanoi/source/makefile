# Specify extensions of files to delete when cleaning
CLEANEXTS   = o a

CC = gcc
CFLAGS = -Wall -g

# Specify the target file and the install directory
OUTPUTFILE  = libhanoilib.a
INSTALLDIR  = ../binaries
HEADERDIR = ../headers

# Default target
.PHONY: all
all: $(OUTPUTFILE)

# Build libhanoilib.a
$(OUTPUTFILE): hanoi.o
	ar r $@ $^
	ranlib $@

hanoi.o: hanoi.c hanoi.h
	$(CC) $(CFLAGS) -c hanoi.c


.PHONY: test
test:
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -o tester main.o -L. -lhanoilib -lm


.PHONY: install
install:
	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)
	mkdir -p $(HEADERDIR)
	cp -p *.h $(HEADERDIR)

.PHONY: clean
clean:
	for file in $(CLEANEXTS); do rm -f *.$$file; done
	rm tester
