CC=gcc
# warnings all and debugging
CFLAGS=-c -Wall -g
CURRENT_DIR := $(shell basename `pwd`)
THIS_FILE := $(lastword $(MAKEFILE_LIST))

all: hw2

hw2: shell.o hw2.o
	$(CC) shell.o hw2.o -o hw2

shell.o: shell.c
	$(CC) $(CFLAGS) shell.c

hw2.o:	hw2.c
	$(CC) $(CFLAGS) hw2.c

clean:
	/bin/rm -f hw2 *.o *~

run:
	./hw2

tarball:
	@$(MAKE) -f $(THIS_FILE) clean
	tar -cvzf ../$(CURRENT_DIR).tgz -C.. $(CURRENT_DIR)
