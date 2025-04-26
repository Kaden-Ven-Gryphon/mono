# Specify extensions of files to delete when cleaning
CLEANEXTS   = o a 

CC = gcc
CFLAGS = -Wall

# Specify the target file and the install directory
OUTPUTFILE  = libcwslib.a
INSTALLDIR  = ../binaries

# Default target
.PHONY: all
all: $(OUTPUTFILE)

# Build libcwslib.a
$(OUTPUTFILE): conwayssoldiers.o
	ar r $@ $^
	ranlib $@

conwatssoldiers.o: conwayssoldiers.c conwayssoldier.h
	$(CC) $(CFLAGS) -c conwatssoldiers.c


.PHONY: test
test:
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -o tester main.o -L. -lcwslib


.PHONY: install
install:
	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)

.PHONY: clean 
clean:
	for file in $(CLEANEXTS); do rm -f *.$$file; done
	rm tester


