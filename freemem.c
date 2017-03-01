/**
 * CSE374 Winter 2017
 * Homework 6 Memory Management
 * Josh(Jiashuo) Zhang 1365330
 * Ethan(Chiho) Kim 0963203 
 * Feb 20, 2017
 * Implementation of function freemem
 * This program returns the given block of memory back to the pool of available
 * memory storage(freelist). The user should to give valid pointer for it functions 
 * properly. It checks for NULL pointer but not other cases. The operation is
 * undefined if the pointer given is invalid.
 */

#include <stdint.h>
#include <stdio.h>
#include "mem_impl.h"

#define HEADER_SIZE 16
#define REQ_SIZE 1000
#define TH 1000

// Function prototypes
void insertBlock(FreeBlock* freeBlock);
void combineBlocks(FreeBlock* A, FreeBlock* B);

// Return the given block memory back to the free list
void freemem(void* p) {
  // Return immediately if p is NULL
  if (!p) {
    return;
  }
  
  FreeBlock* current = freeList;
  FreeBlock* freeBlock = (FreeBlock*) ((uintptr_t)p-HEADER_SIZE);

  insertBlock(freeBlock);

  // Check the freelist and combine adjacent blocks
  while (current && current->next) {
    if ((uintptr_t)current+current->size+HEADER_SIZE
	== (uintptr_t)current->next) {
      combineBlocks(current, current->next);
    } else {
      current = current->next;
    }
  }
}

// Insert the freeblock into freelist in the right position
// to maintain the list sorted
void insertBlock(FreeBlock* freeBlock) {
  FreeBlock* current = freeList;
 
  // If the entire list is empty, given block is the front of the freelist
  if (!current) {
    freeList = freeBlock;
    return;
  } else {
    // If the size of freeblock is smaller than that of the current block,
    // link the freeblock in front of the current block
    if ((uintptr_t)freeBlock < (uintptr_t)current) {
      freeBlock->next = current;
      freeList = freeBlock;
    } else {
      // Find the appropriate position of the block in the list
      while (current->next && 
	     (uintptr_t)freeBlock > (uintptr_t)current->next) {
        current = current->next;
      } 
      // If the size of freeblock is greater than every block
      // in the list, link freeblock to the end of the list
      if (!current->next) {
        current->next = freeBlock;
	return;
	// Link the freeblock before a block with greater size
	// and after a block with smaller size
      } else {
	freeBlock->next = current->next;
        current->next = freeBlock;
      }
    }
  }
}

// Combine two blocks into a single block
void combineBlocks(FreeBlock* A, FreeBlock* B) {
  A->size += B->size + HEADER_SIZE;
  A->next = B->next;
}
