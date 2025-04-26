# Specify extensions of files to delete when cleaning
CLEANEXTS   = o a

CC = gcc
CFLAGS = -Wall -g

# Specify the target file and the install directory
OUTPUTFILE  = libticktacknnlib.a
INSTALLDIR  = ../binaries
HEADERDIR = ../headers

# Default target
.PHONY: all
all: $(OUTPUTFILE)

# Build libticktacknnlib.a
$(OUTPUTFILE): ticktack.o ticktackutil.o nnet.o
	ar r $@ $^
	ranlib $@

phaseten.o: ticktack.c ticktack.h
	$(CC) $(CFLAGS) -c ticktack.c

phasetenutil.o: ticktackutil.c ticktackutil.h
	$(CC) $(CFLAGS) -c ticktackutil.c
nnet.o: nnet.c nnet.h
	$(CC) $(CFLAGS) -c nnet.c -lm

.PHONY: test
test:
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -o tester main.o -L. -lticktacknnlib -lm


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
