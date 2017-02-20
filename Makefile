# CSE 374 17wi HW5
# Josh(Jiashuo) Zhang 1365330
# Feb 15, 2017
# Makefile for t9 program

CC = gcc
all: bench functions

bench: bench.o mem.h
	gcc -Wall -g -std=c11 -o bench bench.o

functions: getmem.o freemem.o get_mem_stats.o print_heap.o
	gcc -Wall -g -std=c11 -o functions getmem.o freemem.o get_mem_stats.o print_heap.o

getmem.o: getmem.c mem.h
	gcc -Wall -g -std=c11 -c getmem.c

freemem.o: freemem.c mem.h
	gcc -Wall -g -std=c11 -c freemem.c

get_mem_stats.o: get_mem_stats.c mem.h
	gcc -Wall -g -std=c11 -c get_mem_stats.c

print_heap.o: print_heap.c mem.h
	gcc -Wall -g -std=c11 -c print_heap.c

mem_utils.o: mem_utils.c mem_impl.h
	gcc -Wall -g -std=c11 -c mem_utils.c

clean:
	rm -f *.o bench *~