# Specify extensions of files to delete when cleaning
CLEANEXTS = o a

CC = gcc
CFLAGS = -Wall
DEBUGFLAGS =
CONFIGDEF =

# Specify the target file and the install directory
LIBNAME = binimglib
OUTPUTFILE  = lib$(LIBNAME).a
OBJECTS = binpypng.o binimg.o gateimgs.o
INSTALLDIR  = ../binaries

.PHONY: all
all: $(OUTPUTFILE)
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -o tester main.o -L. -l$(LIBNAME) -lm




# Build libbinimglib.a
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

