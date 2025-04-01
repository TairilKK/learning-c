#include <stdio.h>
#include <stdint.h>
#include "06_memory.h"

#define BUFFER_SIZE 1000

int main(void) {
    uint8_t buffer[BUFFER_SIZE];

    memory_init(buffer, BUFFER_SIZE);
    uint8_t *ptr = memory_malloc(10);
    memory_free(ptr);

    return 0;
}
