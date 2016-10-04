CC=gcc
CFLAGS=-Wall -g     # replace -g with -O2 if speed needed AFTER debugging
OBJS=poisson.o sched_compare.o procs.o procheap.o

all: sched_compare

sched_compare: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o sched_compare -lm

poisson.o: poisson.c
	$(CC) $(CFLAGS) -c poisson.c

procs.o: procs.c procs.h poisson.h
	$(CC) $(CFLAGS) -c procs.c

procheap.o: procheap.c procs.h
	$(CC) $(CFLAGS) -c procheap.c

sched_compare.o: sched_compare.c procs.h
	$(CC) $(CFLAGS) -c sched_compare.c

clean:
	/bin/rm -f sched_compare $(OBJS)
