#include <stdio.h>
#include <string.h>
#include "07_heap.h"

int main(void) {
    heap_setup();
    printf("Poczatkowy heap:\n");
    display_memory();

    //printf("\nReverse:\n");
    //display_memory_rev();

    uint8_t *(p)[4];

    p[0] = heap_malloc(32);

    printf("\nPo uzyciu funkcji heap_malloc(32):\n");
    display_memory();
    printf("\nreverse:\n");
    display_memory_rev();

    p[1] = heap_malloc(16);
    printf("\nPo uzyciu funkcji heap_malloc(16):\n");
    display_memory();
    printf("\nreverse:\n");
    display_memory_rev();

    //printf("\nReverse:\n");
    //display_memory_rev();

    expand_heap(2*(8 + sizeof(struct heap_chunk_t)));

    printf("\nPo uzyciu funkcji expand:\n");
    display_memory();
    //printf("\nReverse:\n");
    //display_memory_rev();

    p[2] = heap_malloc(8);
    p[3] = heap_malloc(8);

    printf("\nPo uzyciu funkcji malloc po expand:\n");
    display_memory();
    //printf("\nReverse:\n");
    //display_memory_rev();



    ((void)p);

    heap_clean();

    return 0;
}


