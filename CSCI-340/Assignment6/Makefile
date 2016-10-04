CC=gcc
CFLAGS=-c -O -Wall -g -std=gnu90

all: hw6

hw6: mcsim.o hw6.o
	$(CC) dpsim.o hw6.o -o hw6 -lpthread -lrt

dpsim.o: dpsim.c
	$(CC) $(CFLAGS) dpsim.c

hw6.o: hw6.c
	$(CC) $(CFLAGS) hw6.c

clean:
	/bin/rm -f hw6 *.o *.gz

run:
	./hw6

tarball:
	 # put your tar command here
	 # tar -cvzf <lastname>.tar.gz *
