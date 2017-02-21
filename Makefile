# CSE 374 17wi HW5
# Josh(Jiashuo) Zhang 1365330
# Ethan(Chiho) Kim 0963203
# Feb 15, 2017
# Makefile for t9 program

CC = gcc -Wall -g -std=c11
MEMO = getmem.o freemem.o get_mem_stats.o print_heap.o

all: bench functions

bench: bench.o $(MEMO)
	$(CC) -o bench bench.o $(MEMO)

functions: $(MEMO)
	$(CC) -o functions $(MEMO)

bench.o: bench.c mem.h
	$(CC) -o bench.o bench.c

getmem.o: getmem.c mem.h mem_impl.h
	$(CC) -c getmem.c

freemem.o: freemem.c mem.h mem_impl.h
	$(CC) -c freemem.c

get_mem_stats.o: get_mem_stats.c mem.h
	$(CC) -c get_mem_stats.c

print_heap.o: print_heap.c mem.h
	$(CC) -c print_heap.c

mem_utils.o: mem_utils.c mem_impl.h
	$(CC) -c mem_utils.c

clean:
	rm -f *.o bench *~