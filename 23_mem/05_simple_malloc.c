#include <stdio.h>
#include <stdint.h>

struct memory_manager_t
{
    void *memory_start;
    size_t memory_size;
    struct memory_chunk_t *first_memory_chunk;
};

struct memory_chunk_t
{
    struct memory_chunk_t* prev;
    struct memory_chunk_t* next;
    size_t size;
    int free;
};

void memory_init(void *address, size_t size);
void *memory_malloc(size_t size);
void memory_free(void *address);

struct memory_manager_t memory_manager;

int main(void) {
    printf("Hello, World!\n");
    return 0;
}


void memory_init(void *address, size_t size){
    if(address == NULL)
        return;

    memory_manager.memory_start=address;
    memory_manager.memory_size = size;
    memory_manager.first_memory_chunk = NULL;
}

void *memory_malloc(size_t size){
    if (memory_manager.memory_start == NULL || size == 0)
        return NULL;

    size_t used_size=0;
    struct memory_chunk_t *chunk = memory_manager.first_memory_chunk,
            *prev_chunk = NULL;

    if(chunk == NULL && size < memory_manager.memory_size) {
        chunk = (struct memory_chunk_t *) ((uint8_t *) memory_manager.memory_start);
        chunk->next=NULL;
        chunk->prev=NULL;
        chunk->free=0;
        chunk->size=size;
        memory_manager.first_memory_chunk = chunk;
        return (uint8_t *)chunk + sizeof(struct memory_chunk_t);
    }

    while(chunk != NULL) {
        if (chunk->free && chunk->size >= size)
            break;
        used_size += chunk->size + sizeof(struct memory_chunk_t);
        prev_chunk = chunk;
        chunk = chunk->next;
    }

    if(chunk == NULL) {
        if(used_size + size >= memory_manager.memory_size)
            return NULL;

        chunk = (struct memory_chunk_t *) ((uint8_t *) prev_chunk + prev_chunk->size);
        chunk->next = NULL;
        chunk->prev = prev_chunk;
        prev_chunk->next = chunk;
    }

    chunk->free = 0;
    chunk->size = size;

    if(memory_manager.first_memory_chunk == NULL){
        memory_manager.first_memory_chunk = chunk;
    }

    return (uint8_t *)chunk + sizeof(struct memory_chunk_t);
}

void remove_free_duplicate(void){
    if(memory_manager.memory_start == NULL || memory_manager.first_memory_chunk == NULL)
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
    if (address == NULL || memory_manager.memory_start == NULL)
        return;

    struct memory_chunk_t *chunk = memory_manager.first_memory_chunk;
    while (chunk!=NULL){
        if(address == chunk + 1){
            if(chunk->free)
                return;
            chunk->free = 1;
            if(chunk->next != NULL)
                chunk->size = ((uint8_t*)chunk->next - (uint8_t*)chunk);
            break;
        }
        chunk = chunk->next;
    }
    remove_free_duplicate();
}


