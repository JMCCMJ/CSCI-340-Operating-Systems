CC=gcc
# warnings all and debugging
CFLAGS=-c -Wall -g
CURRENT_DIR := $(shell basename `pwd`)
THIS_FILE := $(lastword $(MAKEFILE_LIST))

all: hw4

hw4: shell.o hw4.o
	$(CC) -g shell.o hw4.o -o hw4

shell.o: shell.c
	$(CC) $(CFLAGS) shell.c

hw4.o:	hw4.c
	$(CC) $(CFLAGS) hw4.c

clean:
	/bin/rm -f hw4 *.o *~

run:
	./hw4

tarball:
	@$(MAKE) -f $(THIS_FILE) clean
	tar -cvzf ../$(CURRENT_DIR).tgz -C.. $(CURRENT_DIR)
