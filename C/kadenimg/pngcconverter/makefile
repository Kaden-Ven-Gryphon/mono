# Specify extensions of files to delete when cleaning
CLEANEXTS   = o a

CC = gcc
CFLAGS = -Wall -g

# Specify the target file and the install directory
OUTPUTFILE  = libkadenimglib.a
INSTALLDIR  = ../binaries
HEADERDIR = ../headers

# Default target
.PHONY: all
all: $(OUTPUTFILE)

# Build libhanoilib.a
$(OUTPUTFILE): kadenimgpng.o kadenzlib.o kadenbinary.o
	ar r $@ $^
	ranlib $@

kadenimgpng.o: kadenimgpng.c kadenimgpng.h
	$(CC) $(CFLAGS) -c kadenimgpng.c

kadenzlib.o: kadenzlib.c kadenzlib.h
	$(CC) $(CFLAGS) -c kadenzlib.c
	
kadenbinary.o: kadenbinary.c kadenbinary.h
	$(CC) $(CFLAGS) -c kadenbinary.c


.PHONY: test
test:
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -o tester main.o -L. -lkadenimglib -lm


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
