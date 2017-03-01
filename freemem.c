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
<<<<<<< HEAD
    check_heap();
    if (!p) {
        goto END;
    }

    FreeBlock* pHead = (FreeBlock*)((uintptr_t)p - HEADER_SIZE);
    FreeBlock* temp = freeList;

    uintptr_t endAddress = (uintptr_t)pHead + pHead->size;
    
    // FreeList null, insert it anyways
    if (!freeList) {
        freeList = pHead;
        freeList->next = temp;
        goto END;
    }

    // Merge with preceding and following blocks
    if ((uintptr_t)pHead == ((uintptr_t)freeList + freeList->size) && freeList->next &&
            endAddress == (uintptr_t)freeList->next) {
        freeList->size = freeList->size + pHead->size + freeList->next->size;
        freeList->next = freeList->next->next;
        goto END;
    // Merge with following block
    } else if (endAddress == (uintptr_t)freeList) {
        freeList = pHead;
        freeList->size = freeList->size + temp->size;
        freeList->next = temp->next;
        goto END;
    // Merge with preceding block
    } else if ((uintptr_t)pHead == ((uintptr_t)freeList + freeList->size)) {
        freeList->size = freeList->size + pHead->size;
        goto END;
    // Add to the very beginning
    } else if (pHead < freeList) {
        pHead->next = freeList;
        freeList = pHead;
        goto END;
    }
    
    // Find the correct position to insert block
    while (temp->next) {
        uintptr_t prevEnd = (uintptr_t)temp->next + temp->next->size;
        // Merge with preceding and following block
        if ((uintptr_t)pHead == prevEnd && endAddress == (uintptr_t)temp->next->next) {
            temp->next->size = temp->next->size + pHead->size + temp->next->next->size;
            temp->next->next = temp->next->next->next;
            goto END;
        // Merge with preceding block
        } else if ((uintptr_t)pHead == prevEnd) {
            temp->next->size = temp->next->size + pHead->size;
            goto END;
        // Merge with following block
        } else if (endAddress == (uintptr_t)temp->next) {
            pHead->next = temp->next->next;
            pHead->size = pHead->size + temp->next->size;
            temp->next = pHead;
            goto END;
        // Current address to big, continue searching
        } else if (pHead > temp->next) {
            temp = temp->next;
        // Current block needs to be inserted here, stop searching
        } else if (pHead < temp->next) {
            break;
        }
        
    }
    // Simply insert it, no merge
    pHead->next = temp->next;
    temp->next = pHead;

    END:
    check_heap();
=======
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
>>>>>>> 8476dbb8d188fe84cd2953e889fb0c5965808b07
}
