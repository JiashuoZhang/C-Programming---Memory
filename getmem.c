/**
 * CSE374 Winter 2017
 * Homework 6 Memory Management
 * Josh(Jiashuo) Zhang 1365330
 * Ethan(Chiho) Kim 0963203 
 * Feb 20, 2017
 * Implementation of function getmem
 * The program returns a pointer to a block of memory with at least size of user
 * request. User needs to give appropriate size for it to properly function. The memory
 * blocks allocated by this program are 16-byte aligned in address boundary.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mem_impl.h"

// Function prototypes
FreeBlock* split(FreeBlock* block, uintptr_t size);

// Return pointer to a memory block with at least size of given parameter
void* getmem(uintptr_t size) {
    if (size <= 0) {
        return NULL;
    }

    // Make sure multiple of 16 in size including the header
    uintptr_t realSize = size + HEADER_SIZE;
    uintptr_t alignSize = realSize % 16 ? (1 + realSize / 16) * 16 : realSize;

    FreeBlock* current;
    if (!freeList) {
        if (alignSize > REQ_SIZE) { // Default size not big enough
            current = (FreeBlock*)malloc(alignSize); // Get larger chunk from OS
            current->size = alignSize;
            current->next = NULL;
            return (void*)((uintptr_t)current + HEADER_SIZE);
        } else {
            // Get 8K bytes memory from OS
            current = (FreeBlock*)malloc(REQ_SIZE); 
            current->size = REQ_SIZE;
            current->next = NULL;
            // Split block if necessary
            freeList = split(current, alignSize);
            return (void*)((uintptr_t)current + HEADER_SIZE);
        }
    } else {
        current = freeList;
        // The first block in list is big enough
        if (freeList->size >= alignSize) {

            freeList = split(freeList, alignSize);
            return (void*)((uintptr_t)current + HEADER_SIZE);
        }
        
        // Loop through free list to find block
        while (current->next != NULL) {
            if (current->next->size >= alignSize) {
                break;
            }
            current = current->next;
        }
        // Fail to find a block big enough
        if (!current->next) {
            
            if (alignSize > REQ_SIZE) { // Default size not big enough
                current = (FreeBlock*)malloc(alignSize);
                current->size = alignSize;
                current->next = NULL;
                return (void*)((uintptr_t)current + HEADER_SIZE);
            } else {                    // Default size big enough
                current = (FreeBlock*)malloc(REQ_SIZE);
                current->size = REQ_SIZE;
                current->next = NULL;
                FreeBlock* remainder = split(current, alignSize);
                
                if (!remainder) {
                    return (void*)((uintptr_t)current + HEADER_SIZE);
                } else if (remainder < freeList || !freeList) {
                    remainder->next = freeList;
                    freeList = remainder;
                    return (void*)((uintptr_t)current + HEADER_SIZE);
                } else {
                    FreeBlock* temp = freeList;
                    // Find the correct position to insert
                    while (temp->next && remainder > temp->next) {
                        temp = temp->next;
                    }
                    // Insert
                    remainder->next = temp->next;
                    temp->next = remainder;
                    return (void*)((uintptr_t)current + HEADER_SIZE);
                }
            }
        } else { // Found a good size block in free list
            FreeBlock* temp = current->next;
            current->next = split(current->next, alignSize);
            return (void*)((uintptr_t)temp + HEADER_SIZE);
        }
    }

    return NULL;
}

FreeBlock* split(FreeBlock* block, uintptr_t size) {
    // Remaining block greater than threshold
    if (block->size - size >= TH) {
        FreeBlock* current = block;
        // Set header for remaining block

        block = (FreeBlock*)((uintptr_t)current + size);
        block->size = current->size - size;
        block->next = current->next;

        // Set current block ready for client
        current->size = size;
        current->next = NULL;
        return block;
    }
    return block->next;
}
