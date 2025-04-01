//
// Created by jdobr on 16.11.2024.
//

#ifndef MEM_06_MEMORY_H
#define MEM_06_MEMORY_H

#include <stdio.h>
#include <stdint.h>

#define FENCE_SIZE (size_t)16
#define FENCE_VALUE (uint8_t)0

struct memory_manager_t
{
    void *memory_start;
    size_t memory_size;
    struct memory_chunk_t *first_memory_chunk;
};

struct memory_chunk_t
{
    struct memory_chunk_t *prev;
    struct memory_chunk_t *next;
    size_t size;
    int free;
};

void memory_init(void *address, size_t size);
void *memory_malloc(size_t size);
void memory_free(void *address);

int heap_validate(void);

struct memory_manager_t memory_manager;

#endif // MEM_06_MEMORY_H
