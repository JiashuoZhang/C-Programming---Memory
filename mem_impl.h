/**
 * CSE374 Winter 2017
 * Homework 6 Memory Management
 * Josh(Jiashuo) Zhang 1365330
 * Ethan(Chihio) Kim 0963203 
 * Feb 20, 2017
 * Header file for internal functions for memory manager.
 * The functions included in this file are not public functions 
 * for clients to use.
 */

#ifndef MEM_IMPL_H
#define MEM_IMPL_H

typedef struct FreeList {
    uintptr_t size;
    struct FreeList* next;
} FreeBlock;
// Check errors for free list structure

FreeBlock* freeList; // The head of free list, null if empty

void check_heap();

#endif