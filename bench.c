/**
 * CSE374 Winter 2017
 * Homework 6 Memory Management
 * Josh(Jiashuo) Zhang 1365330
 * Ethan(Chiho) Kim 0963203 
 * Feb 20, 2017
 * Bench program for testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "mem_impl.h"
#include "mem.h"

int main(int argc, char** argv) {
    char* x = getmem(1);
    char* y = getmem(7744);
    char* z = getmem(1);

    // char* a = getmem(1);
    // char* b = getmem(7744);
    // char* c = getmem(1);

    // char* i = getmem(1);
    // char* j = getmem(7744);
    // char* k = getmem(1);
    
    printf("*****************\n");
    freemem(x);
    printf("heap\n");
    print_heap();
    freemem(y);
    printf("heap\n");
    print_heap();
    freemem(z);
    printf("heap\n");
    print_heap();
    printf("*****************\n");
    // freemem(k);
    // printf("heap\n");
    // print_heap();
    // freemem(i);
    // printf("heap\n");
    // print_heap();
    // freemem(j);
    // printf("heap\n");
    // print_heap();
    // printf("*****************\n");
    // freemem(c);
    // printf("heap\n");
    // print_heap();
    // freemem(b);
    // printf("heap\n");
    // print_heap();
    // freemem(a);
    // printf("heap\n");
    // print_heap();
    // printf("*****************\n");

    uintptr_t size, totalFree, nFreeBlocks;
    get_mem_stats(&size, &totalFree, &nFreeBlocks);
    printf("%lu %lu %lu\n", size, totalFree, nFreeBlocks);
    // char*z = getmem(128);
    // FreeBlock* zhead = (FreeBlock*)((uintptr_t)z - 16);
    // printf("%d\n", zhead);
    // printf("%lu\n", zhead->size);

    // printf("%d\n", freeList);
    // printf("%lu\n", freeList->size);
    // printf("%d\n", freeList->next);
    // printf("%d\n\n\n", freeList->next->size);

    // ////*********************************/////
    // // Test found good block
    // char* a = getmem(128);
    // char* b = getmem(128);
    // char* c = getmem(128);
    
    return 0;
}

