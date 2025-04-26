# Specify extensions of files to delete when cleaning
CLEANEXTS = o a

CC = gcc
CFLAGS = -Wall
DEBUGFLAGS =
CONFIGDEF =

# Specify the target file and the install directory
LIBNAME = pnggatelib
OUTPUTFILE  = lib$(LIBNAME).a
OBJECTS = gategraph.o binpypng.o binimg.o gateimgs.o gatecircuits.o
INSTALLDIR  = ../binaries

.PHONY: all
all: $(OUTPUTFILE)
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -o tester main.o -L. -l$(LIBNAME) -lm




# Build pnggatelib.a
$(OUTPUTFILE): $(OBJECTS)
	ar r $@ $^
	ranlib $@

# Make object files
%.o : %.c %.h
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(CONFIGDEF) -c $< -o $@


.PHONY: install
install:
	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)


.PHONY: clean
clean:
	for file in $(CLEANEXTS); do rm -f *.$$file; done
	rm tester
