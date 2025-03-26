//
// Created by jdobr on 19.08.2023.
//

#include <stdio.h>
#include <string.h>

#include "12_message_t.h"

int load_data(struct message_t *cp, int size, const char *filename) {
    if(cp == NULL || filename == NULL || size<1)
        return -1;

    FILE* file = fopen(filename, "rb");
    if (!file)
        return -2;


    unsigned int n;
    if (fread(&n, sizeof(unsigned int), 1, file) != 1) {
        fclose(file);
        return -3;
    }

    if (n % sizeof(struct message_t) != 0) {
        fclose(file);
        return -3;
    }

    int structs_to_read = n / sizeof(struct message_t);
    if (structs_to_read > size) {
        structs_to_read = size;
    }

    if (fread(cp, sizeof(struct message_t), structs_to_read, file) != (long unsigned int)structs_to_read) {
        fclose(file);
        return -3;
    }

    fclose(file);
    return structs_to_read;
}

int decode_message(const struct message_t *cp, int size, char *msg, int text_size) {
    if (cp == NULL || msg == NULL || size <= 0 || text_size <= 0)
        return 1;

    char *hidden_ptr;
    int bytes_copied = 0;

    for (int i = 0; i < size && bytes_copied < text_size - 1; i++) {
        hidden_ptr = (char*)(&((cp+i)->a)) + 1;
        for (int j = 0; j < 7 && bytes_copied < text_size - 1; j++)
            *(msg+bytes_copied++) = *(hidden_ptr+j);

        hidden_ptr = (char*)(&((cp+i)->c)) + sizeof(int);
        for (int j = 0; j < 4 && bytes_copied < text_size - 1; j++)
            *(msg+bytes_copied++) = *(hidden_ptr+j);
    }
    *(msg+bytes_copied) = '\0';

    return 0;
}
