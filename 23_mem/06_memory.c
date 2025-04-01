//
// Created by jdobr on 16.11.2024.
//
#include <stdint.h>
#include "06_memory.h"

void memory_init(void *address, size_t size){
    if(address == NULL)
        return;

    memory_manager.memory_start = address;
    memory_manager.memory_size = size;
    memory_manager.first_memory_chunk = NULL;
}

void create_fence(struct memory_chunk_t *chunk){
    if(chunk == NULL)
        return;
    for(size_t i = 0; i < FENCE_SIZE; ++i) {
        *((uint8_t *) chunk + sizeof(struct memory_chunk_t) + i) = FENCE_VALUE;
        *((uint8_t *) chunk + sizeof(struct memory_chunk_t) + FENCE_SIZE + chunk->size + i) = FENCE_VALUE;
    }
}

void *memory_malloc(size_t size){
    if (size == 0 || heap_validate())
        return NULL;


    size_t used_size=0, real_size = size + 2 * FENCE_SIZE;
    struct memory_chunk_t *chunk = memory_manager.first_memory_chunk, *prev_chunk = NULL;

    // Check if first memory chunk is NULL
    if(chunk == NULL && real_size < memory_manager.memory_size) {
        chunk = (struct memory_chunk_t *) memory_manager.memory_start;
        chunk->next = NULL;
        chunk->prev = NULL;
        chunk->free = 0;
        chunk->size = size;

        create_fence(chunk);
        memory_manager.first_memory_chunk = chunk;
        return (uint8_t *)chunk + sizeof(struct memory_chunk_t) + FENCE_SIZE;
    }

    // Finding first free chunk or NULL if not found
    while(chunk != NULL) {
        if (chunk->free && real_size < chunk->size )
            break;
        used_size += chunk->size + sizeof(struct memory_chunk_t) + 2 * FENCE_SIZE;
        prev_chunk = chunk;
        chunk = chunk->next;
    }

    // If chunk not found
    if(chunk == NULL) {
        if(used_size + real_size >= memory_manager.memory_size)
            return NULL;

        chunk = (struct memory_chunk_t *) ((uint8_t *)prev_chunk + prev_chunk->size + sizeof(struct memory_chunk_t) + 2 * FENCE_SIZE);
        chunk->next = NULL;
        chunk->prev = prev_chunk;
        prev_chunk->next = chunk;
    }

    chunk->free = 0;
    chunk->size = size;
    create_fence(chunk);

    return (uint8_t *)chunk + sizeof(struct memory_chunk_t) + FENCE_SIZE;
}

void remove_free_duplicate(void){
    if(memory_manager.first_memory_chunk == NULL)
        return;

    struct memory_chunk_t* iter = memory_manager.first_memory_chunk;
    while(iter->next != NULL){
        if(iter->free && iter->next->free) {
            iter->size += iter->next->size + sizeof(struct memory_chunk_t);
            iter->next = iter->next->next;
            if(iter->next)
                iter->next->prev = iter;
            continue;
        }
        iter = iter->next;
    }

    // remove last element if element is free
    if(iter->free && iter->next == NULL && iter->prev)
        iter->prev->next = NULL;


    // check if list has only free element
    if(memory_manager.first_memory_chunk->free &&
       memory_manager.first_memory_chunk->prev == NULL &&
       memory_manager.first_memory_chunk->next == NULL)
        memory_manager.first_memory_chunk = NULL;
}

void memory_free(void *address){
    if (address == NULL || heap_validate())
        return;

    struct memory_chunk_t *chunk = memory_manager.first_memory_chunk;
    while (chunk!=NULL){
        if(address == (uint8_t*)chunk + sizeof(struct memory_chunk_t) + FENCE_SIZE){
            if(chunk->free)
                return;
            chunk->free = 1;
            if(chunk->next != NULL)
                chunk->size = ((uint8_t*) chunk->next - (uint8_t*) chunk) - sizeof(struct memory_chunk_t);
            break;
        }
        chunk = chunk->next;
    }
    remove_free_duplicate();
}

int heap_validate(void){
    if(memory_manager.memory_start == NULL || memory_manager.memory_size == 0)
        return 1;

    struct memory_chunk_t *chunk = memory_manager.first_memory_chunk;
    while(chunk != NULL) {
        for (size_t i = 0; i < FENCE_SIZE; ++i) {
            if(chunk->free == 0) {
                // chunk is not free
                if (*((uint8_t *) chunk + sizeof(struct memory_chunk_t) + i) != FENCE_VALUE ||
                    *((uint8_t *) chunk + sizeof(struct memory_chunk_t) + chunk->size + FENCE_SIZE + i ) != FENCE_VALUE)
                    return 1;
            } else {
                // chunk is free
                if (*((uint8_t *) chunk + sizeof(struct memory_chunk_t) + i) != FENCE_VALUE ||
                    *((uint8_t *) chunk + sizeof(struct memory_chunk_t) + chunk->size - FENCE_SIZE + i ) != FENCE_VALUE)
                    return 1;
            }
        }
        chunk = chunk->next;
    }

    return 0;
}


