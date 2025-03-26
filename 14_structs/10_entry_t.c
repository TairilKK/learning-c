//
// Created by jdobr on 18.08.2023.
//
#include <stdio.h>
#include <string.h>

#include "10_entry_t.h"


void display(const struct entry_t* p)
{
    if( p == NULL ) return;
    printf("Name: %s\n"
           "Last name: %s\n"
           "Phone number: %d\n", p->name, p->last_name, p->number);
}

#define MAX_LINE_LEN 256

int load_phonebook_t(const char *filename, struct entry_t* p, int size)
{
    if(filename == NULL || p == NULL || size < 1) return -1;

    FILE *f = fopen(filename, "r");
    if(f == NULL) return -2;

    char line[MAX_LINE_LEN];
    int record_counter = 0;

    while(record_counter < size && fgets(line, sizeof(line), f)) {
        if(sscanf(line, "%19[^|]| %39[^|]| %d", (p + record_counter)->name, (p + record_counter)->last_name, &((p + record_counter)->number)) == 3) {
            *((p + record_counter)->name + strlen((p + record_counter)->name) - 1) = '\0';
            *((p + record_counter)->last_name + strlen((p + record_counter)->last_name) - 1) = '\0';
            record_counter++;
        }
    }

    fclose(f);
    return record_counter;
}

const struct entry_t* find_by_last_name(const struct entry_t* p, int size, const char *last_name)
{
    if(p == NULL || size<1 || last_name == NULL) return NULL;
    for(int i = 0; i<size; ++i)
    {
        if (!strcmp(last_name, (p + i)->last_name))
            return (p + i);
    }
    return NULL;
}
