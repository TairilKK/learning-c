//
// Created by jdobr on 30.08.2023.
//

#ifndef INC_05_BIG_NUMBERS_H
#define INC_05_BIG_NUMBERS_H

struct big_numbers_t {
    int size;
    int capacity;
    char **big_number;
};

int create(struct big_numbers_t *bn, int capacity);
int create_big_numbers(struct big_numbers_t **bn, int capacity);

void destroy(struct big_numbers_t *bn);
void destroy_big_numbers(struct big_numbers_t **bn);

int isNumber(char * a);
int add_big_number(struct big_numbers_t *bn, const char *big_number);

void display(const struct big_numbers_t *bn);

#endif //INC_05_BIG_NUMBERS_H
