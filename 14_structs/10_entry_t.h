//
// Created by jdobr on 18.08.2023.
//

#ifndef INC_15_ENTRY_T_H
#define INC_15_ENTRY_T_H

struct entry_t
{
    char name[20];
    char last_name[40];
    int number;
};

void display(const struct entry_t *p);
int load_phonebook_t(const char *filename, struct entry_t *p, int size);
const struct entry_t *find_by_last_name(const struct entry_t *p, int size, const char *last_name);

#endif // INC_15_ENTRY_T_H
