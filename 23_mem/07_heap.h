//
// Created by jdobr on 19.11.2024.
//

#ifndef MEM_PROJECT_HEAP_H
#define MEM_PROJECT_HEAP_H

#include <stdio.h>
#include <unistd.h>

#define FENCE_SIZE 16
#define FENCE_VALUE 0

#define MEMORY_SIZE (sizeof(struct heap_manager_t) + 3 * sizeof(struct heap_chunk_t))

enum pointer_type_t
{
    pointer_null,
    pointer_heap_corrupted,
    pointer_control_block,
    pointer_inside_fences,
    pointer_inside_data_block,
    pointer_unallocated,
    pointer_valid
};

struct heap_manager_t
{
    struct heap_chunk_t *head;
    struct heap_chunk_t *tail;

    void *memory_start;
    size_t memory_size;
};

struct heap_chunk_t
{
    struct heap_chunk_t* prev;
    struct heap_chunk_t* next;

    size_t size;
    long free;
};

void display_memory(void);
void display_memory_rev(void);
void* expand_heap(size_t size);

int heap_setup(void);
void heap_clean(void);

void* heap_malloc(size_t size);
void* heap_calloc(size_t number, size_t size);
void* heap_realloc(void* memblock, size_t count);
void  heap_free(void* memblock);

size_t heap_get_largest_used_block_size(void);
enum pointer_type_t get_pointer_type(const void* const pointer);

int heap_validate(void);


#endif //MEM_PROJECT_HEAP_H
