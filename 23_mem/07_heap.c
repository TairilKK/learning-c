//
// Created by jdobr on 19.11.2024.
//
#include <string.h>
#include "07_heap.h"

/* CHUNK POINTERS MACROS */
#define CHUNK_START_FENCE_START(chunk)      ((uint8_t *)(chunk) + sizeof(struct heap_chunk_t))
#define CHUNK_START_FENCE_END(chunk)        ((uint8_t *)(chunk) + sizeof(struct heap_chunk_t) + FENCE_SIZE)
#define CHUNK_DATA(chunk)                   CHUNK_START_FENCE_END(chunk)
#define CHUNK_DATA_END(chunk)               ((uint8_t *)(chunk) + sizeof(struct heap_chunk_t) + FENCE_SIZE + (chunk)->size)
#define CHUNK_END_FENCE_START(chunk)        CHUNK_DATA_END(chunk)
#define CHUNK_END_FENCE_END(chunk)          ((uint8_t *)(chunk) + sizeof(struct heap_chunk_t) + FENCE_SIZE + (chunk)->size + FENCE_SIZE)

// [CCCCCCCCFFFF.......................FFFF??????????] -> CHUNK_START_FENCE_START
//          ^
// [CCCCCCCCFFFF.......................FFFF??????????] -> CHUNK_START_FENCE_END, CHUNK_DATA
//              ^
// [CCCCCCCCFFFF.......................FFFF??????????] -> CHUNK_DATA_END, CHUNK_END_FENCE_START
//                                     ^
// [CCCCCCCCFFFF.......................FFFF??????????] -> CHUNK_END_FENCE_END
//                                         ^


#define BYTES_BETWEEN(pointer_start, pointer_end) ((uint8_t *)(pointer_end) - (uint8_t *)(pointer_start))

struct heap_manager_t *heap_manager=NULL;

void display_memory(void){
    int count = 0;
    struct heap_chunk_t *current = heap_manager->head;

    for(;current != NULL; current=current->next, ++count) {
        printf("Blok pamieci %d o pamieci %zu jest %s\n", count, current->size, current->free ? "WOLNY" : "ZAJETY");
    }
}

void display_memory_rev(void){
    int count = 0;
    struct heap_chunk_t *current = heap_manager->tail;

    for(;current != NULL; current=current->prev, ++count) {
        printf("Blok pamieci %d o pamieci %zu jest %s\n", -count, current->size, current->free ? "WOLNY" : "ZAJETY");
    }
}

int heap_setup(void){
    uint8_t* init_memory = custom_sbrk(MEMORY_SIZE);
    if (init_memory == (void*)-1) {
        return -1;
    }

    memset(init_memory, '?', MEMORY_SIZE); //todo: usunÄÄ na koniec
    heap_manager = (struct heap_manager_t*)init_memory;

    struct heap_chunk_t
            *head = (struct heap_chunk_t*)(init_memory + sizeof(struct heap_manager_t)),
            *tail = (struct heap_chunk_t*)(init_memory + MEMORY_SIZE - sizeof(struct heap_chunk_t)),
            *free = (struct heap_chunk_t*)((uint8_t*)head + sizeof(struct heap_chunk_t));

    heap_manager->head = head;
    heap_manager->tail = tail;
    heap_manager->memory_size = MEMORY_SIZE;
    heap_manager->memory_start = init_memory;

    head->prev = NULL; head->next = free;
    free->prev = head; free->next = tail;
    tail->prev = free; tail->next = NULL;

    head->size = 0; head->free = 0;
    tail->size = 0; tail->free = 0;

    free->size = (size_t)(BYTES_BETWEEN(free, tail) - sizeof(struct heap_chunk_t));
    free->free = 1;

    return 0;
}

void heap_clean(void){
    if (heap_manager == NULL)
        return;

    if (heap_manager->head == NULL || heap_manager->tail == NULL)
        return;

    custom_sbrk(-(heap_manager->memory_size));
    heap_manager=NULL;
}

struct heap_chunk_t* find_largest_free_chunk(void){
    struct heap_chunk_t
            *largest_free_chunk = heap_manager->head,
            *current = heap_manager->head;

    while(current != NULL){
        if(current->free && current->size > largest_free_chunk->size)
            largest_free_chunk = current;
        current = current->next;
    }

    return largest_free_chunk != heap_manager->head ? largest_free_chunk : NULL;
}

void concat_free_chunks(void);

void* expand_heap(size_t size){
    // todo: poprawiÄ funkcjÄ
    if(size < 1)
        return NULL;

    void *expanded_memory = custom_sbrk(size);
    if(expanded_memory == (void*)-1)
        return NULL;

    heap_manager->memory_size += size;

    memset(expanded_memory, 'E', size); //todo: UsunÄÄ po debagowaniu.

    // przenoszenie tail na koniec

    struct heap_chunk_t *old_tail = heap_manager->tail;
    old_tail->size = size - sizeof(struct heap_chunk_t);
    old_tail->next = (struct heap_chunk_t *)((uint8_t *)old_tail + size);
    old_tail->free = 1;

    old_tail->next->prev = old_tail;
    old_tail->next->next = NULL;
    old_tail->next->size = 0;
    old_tail->next->free = 0;

    heap_manager->tail = old_tail->next;

    concat_free_chunks();

    return expanded_memory;
}

void create_fence(struct heap_chunk_t *chunk){
    if(chunk == NULL)
        return;

    for(size_t i = 0; i < FENCE_SIZE; ++i) {
        *(CHUNK_START_FENCE_START(chunk) + i) = FENCE_VALUE;
        *(CHUNK_END_FENCE_START(chunk) + i) = FENCE_VALUE;
    }
}

void* heap_malloc(size_t size){
    if(size < 1 || heap_validate() != 0)
        return NULL;

    size_t req_size = size;
//    size = align_size(size);


    struct heap_chunk_t *free = find_largest_free_chunk();
    if(free != NULL){
        if(free->size < req_size + 2 * FENCE_SIZE)
            // JeĹźeli nie zmieĹci nowego elementu przypisz null
            free = NULL;
    }

    if(free == NULL) {
        void *p = expand_heap(req_size + 2 * FENCE_SIZE + sizeof(struct heap_chunk_t));
        if(p == NULL)
            return NULL;
        free = find_largest_free_chunk();
    }


    if(free->size >= req_size + sizeof(struct heap_chunk_t) + 2 * FENCE_SIZE) {

        // JeĹźeli moĹźna stworzyÄ dodatkowy chunk to go tworze
        struct heap_chunk_t *next = (struct heap_chunk_t *) (CHUNK_START_FENCE_START(free) + size + 2 * FENCE_SIZE);

        next->prev = free;
        next->next = free->next;
        next->next->prev = next;
        free->next = next;

        next->free = 1;
        next->size = (uint8_t *) next->next - (uint8_t *) next - sizeof(struct heap_chunk_t);

    }
    free->size = req_size;
    free->free = 0;
    create_fence(free);
    memset(CHUNK_DATA(free), '1', free->size);
    return CHUNK_DATA(free);
}

void* heap_calloc(size_t number, size_t size){
    void *pointer = heap_malloc(number * size);
    if(pointer == NULL)
        return NULL;

    memset((uint8_t*)pointer, 0, number * size);

    return pointer;
}

struct heap_chunk_t* find_chunk(void* mem){
    for(struct heap_chunk_t *current = heap_manager->head->next;
        current != heap_manager->tail;
        current = current->next) {
        if(mem == CHUNK_DATA(current))
            return current;
    }

    return NULL;
}

void* heap_realloc(void* memblock, size_t count){
    if (heap_validate())
        return NULL;

    if (memblock == NULL)
        return heap_malloc(count);

    if (get_pointer_type(memblock) != pointer_valid)
        return NULL;

    struct heap_chunk_t *chunk = find_chunk(memblock);

    if(chunk == NULL)
        return heap_malloc(count);

    if(count == 0){
        heap_free(memblock);
        return NULL;
    }

    if (count == chunk->size){
        return memblock;
    }

    if (chunk->next->free == 1){
        chunk->next = chunk->next->next;
        chunk->next->prev = chunk;
    }

    if(count < (size_t)BYTES_BETWEEN(chunk, chunk->next) - sizeof(struct heap_chunk_t) - 2 * FENCE_SIZE){
        chunk->size = count;
        create_fence(chunk);
        return memblock;
    }

    if (chunk != heap_manager->tail->prev){
        uint8_t *ptr = heap_malloc(count);
        if(ptr == NULL)
            return NULL;

        memcpy(ptr, CHUNK_DATA(chunk), chunk->size);
        heap_free(CHUNK_DATA(chunk));
        return ptr;
    }

    void *p = expand_heap( count - chunk->size - 2 * FENCE_SIZE);
    if(p == NULL)
        return NULL;

    chunk->size = count;
    chunk->next = heap_manager->tail;
    heap_manager->tail->prev = chunk;
    create_fence(chunk);

    return CHUNK_DATA(chunk);
}

void concat_free_chunks(void){
    struct heap_chunk_t *current = heap_manager->head->next;
    while(current != heap_manager->tail){
        if(current->free && current->next->free){
            current->next = current->next->next;
            current->next->prev = current;
            current->size = BYTES_BETWEEN(current, current->next) - sizeof(struct heap_chunk_t);
        } else {
            current = current->next;
        }
    }
}

void heap_free(void* memblock){
    if(memblock == NULL || heap_validate() != 0)
        return;

    for(struct heap_chunk_t *current = heap_manager->head->next;
        current != heap_manager->tail;
        current = current->next) {

        if((uint8_t*)memblock == CHUNK_DATA(current)){
            current->free = 1;
            current->size = BYTES_BETWEEN(current, current->next) - sizeof(struct heap_chunk_t);
            concat_free_chunks();
            return;
        }
    }
}

size_t heap_get_largest_used_block_size(void){
    if(heap_validate() != 0)
        return 0;

    size_t size = 0;
    for(struct heap_chunk_t *current = heap_manager->head->next;
        current != heap_manager->tail;
        current=current->next) {

        if (size < current->size && current->free == 0)
            size = current->size;
    }
    return size;
}

enum pointer_type_t get_pointer_type(const void* const pointer){
    if(pointer == NULL)
        return pointer_null; // 0

    if(heap_validate())
        return pointer_heap_corrupted; // 1

    // M - manager bytes
    // C - chunk bytes
    // F - fence bytes
    // H - head bytes
    // T - tail bytes
    // . - data

    // [MMMMMMMMHHHHHHHHCCCCCCCCFFFF..................................FFFFTTTTTTTT??????]
    //  ^       ^
    if((uint8_t *) pointer >= (uint8_t *) heap_manager &&
            (uint8_t *) pointer < (uint8_t *)heap_manager + sizeof(struct heap_manager_t))
        return pointer_control_block; // 2

    // [MMMMMMMMHHHHHHHHCCCCCCCCFFFF..................................FFFFTTTTTTTT??????]
    //          ^       ^
    if((uint8_t *)pointer >= (uint8_t *)heap_manager->head &&
       (uint8_t *)pointer < CHUNK_START_FENCE_START(heap_manager->head))
        return pointer_control_block; // 2

    // [MMMMMMMMHHHHHHHHCCCCCCCCFFFF..................................FFFFTTTTTTTT??????]
    //                                                                    ^       ^
    if((uint8_t *)pointer >= (uint8_t *)heap_manager->tail &&
       (uint8_t *)pointer < CHUNK_START_FENCE_START(heap_manager->tail))
        return pointer_control_block; // 2

    for(struct heap_chunk_t* current = heap_manager->head->next;
        current != heap_manager->tail;
        current = current->next){

        // Szukanie chunka pamiÄci przy ktĂłrym znajduje siÄ pointer.
        if((uint8_t*)pointer >= (uint8_t*)current->next)
            continue;

        // [CCCCCCCCFFFF..................................FFFFAAAAAAAA]
        //  ^       ^
        if ((uint8_t *) pointer >= (uint8_t *)current &&
            (uint8_t *) pointer < CHUNK_START_FENCE_START(current))
            return pointer_control_block; // 2

        if(current->free == 1){
            //Chunk jest wolny

            // [CCCCCCCCFFFF..................................FFFFAAAAAAAA]
            //          ^                                         ^
            if ((uint8_t *)pointer >= CHUNK_START_FENCE_START(current) &&
                (uint8_t *)pointer < (uint8_t *)current->next)
                return pointer_unallocated; // 5

        } else {
            // Chunk jest zajÄty

            // [CCCCCCCCFFFF..................................FFFFAAAAAAAA]
            //          ^   ^
            if ((uint8_t *)pointer >= CHUNK_START_FENCE_START(current) &&
                (uint8_t *)pointer < CHUNK_START_FENCE_END(current))
                return pointer_inside_fences; // 3

            // [CCCCCCCCFFFF..................................FFFFAAAAAAAA]
            //                                                ^   ^
            else if ((uint8_t *) pointer >= CHUNK_END_FENCE_START(current) &&
                     (uint8_t *) pointer < CHUNK_END_FENCE_END(current))
                return pointer_inside_fences; // 3

            // [CCCCCCCCFFFF..................................FFFFAAAAAAAA]
            //              ^                                 ^
            else if ((uint8_t *) pointer > CHUNK_DATA(current) &&
                     (uint8_t *) pointer < CHUNK_DATA_END(current))
                return pointer_inside_data_block; // 4

            // [CCCCCCCCFFFF..................................FFFFAAAAAAAA]
            //              ^
            else if ((uint8_t *) pointer == CHUNK_DATA(current))
                return pointer_valid; // 6


            // [CCCCCCCCFFFF..................................FFFF????AAAAAAAA]
            //                                                    ^   ^
            else if ((uint8_t *)pointer >= CHUNK_END_FENCE_END(current) &&
                    (uint8_t *)pointer < (uint8_t*)current->next)
                return pointer_unallocated; // 5
        }
    }
    return pointer_null; // 0
}

int validate_heap_manager(void) {
    if(heap_manager == NULL)
        return 2;

    if(heap_manager != heap_manager->memory_start)
        return 3;

    if(heap_manager->memory_size != BYTES_BETWEEN(heap_manager, heap_manager->tail) + sizeof(struct heap_chunk_t))
        return 3;

    return 0;
}

int validate_head_and_tail(void){
    struct heap_chunk_t *head = heap_manager->head,
            *tail = heap_manager->tail;

    if(head == NULL || tail == NULL)
        return 2;

    if (head->free == 1 || tail->free == 1)
        return 3;

    if(head->size != 0 || tail->size != 0)
        return 3;

    if(head->prev != NULL || tail->next != NULL)
        return 3;

    return 0;
}

int validate_chunk(struct heap_chunk_t *c){

    // prev lub next wychodzi poza pamiÄc w chunku
    if((uint8_t*)c->prev < (uint8_t*) heap_manager->head ||
        (uint8_t*)c->prev >= (uint8_t*) heap_manager->tail)
        return 3;

    if((uint8_t*)c->next <= (uint8_t*) heap_manager->head ||
       (uint8_t*)c->next > (uint8_t*) heap_manager->tail)
        return 3;

    if(c->prev->next != c || c->next->prev != c)
        return 3;

    if(c->free == 0){
        if (c->size > (size_t)BYTES_BETWEEN(c, c->next) - sizeof(struct heap_chunk_t) - 2 * FENCE_SIZE)
            return 3;

        if (c->size == 0 || c->size >= heap_manager->memory_size)
            return 3;

        for(size_t i = 0; i < FENCE_SIZE; ++i){
            if(*(CHUNK_START_FENCE_START(c) + i) != FENCE_VALUE || *(CHUNK_END_FENCE_START(c) + i) != FENCE_VALUE) {
                return 1;
            }
        }
    }
    else if (c->free == 1) {
        if((uint8_t*)c->next != CHUNK_END_FENCE_END(c) - sizeof(struct heap_chunk_t))
            return 3;
    }
    else // free > 1
        return 3;

    return 0;
}

int heap_validate(void){
    int heap_status;

    heap_status = validate_heap_manager();
    if(heap_status != 0)
        return heap_status;

    heap_status = validate_head_and_tail();
    if(heap_status != 0)
        return heap_status;

    for(struct heap_chunk_t *current = heap_manager->head->next;
        current != heap_manager->tail;
        current = current->next) {

        heap_status = validate_chunk(current);
        if(heap_status != 0)
            return heap_status;
    }

    return 0;
}


