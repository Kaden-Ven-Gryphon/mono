# Specify extensions of files to delete when cleaning
CLEANEXTS   = o a

CC = gcc
CFLAGS = -Wall

# Specify the target file and the install directory
OUTPUTFILE  = libp10ailib.a
INSTALLDIR  = ../binaries
HEADERDIR = ../headers

# Default target
.PHONY: all
all: $(OUTPUTFILE)

# Build libcwslib.a
$(OUTPUTFILE): phaseten.o phasetenutil.o
	ar r $@ $^
	ranlib $@

phaseten.o: phaseten.c phaseten.h
	$(CC) $(CFLAGS) -c phaseten.c

phasetenutil.o: phasetenutil.c phasetenutil.h
	$(CC) $(CFLAGS) -c phasetenutil.c

.PHONY: test
test:
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -o tester main.o -L. -lp10ailib


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
