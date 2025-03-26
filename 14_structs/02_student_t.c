//
// Created by jdobr on 18.08.2023.
//
#include <stdio.h>

#include "02_student_t.h"

struct student_t* read(struct student_t* p, int *err_code)
{
    if(p == NULL){ ERROR(1); return NULL; }

    if (scanf("%19[^,\n]", p->name) != 1) {
        ERROR(1);
        return NULL;
    }

    char temp;
    if (scanf("%c", &temp) != 1 || temp != ',') {
        ERROR(1);
        return NULL;
    }
    if (scanf("%c", &temp) != 1 || temp != ' ') {
        ERROR(1);
        return NULL;
    }

    if (scanf("%39[^,\n]", p->surname) != 1) {
        ERROR(2);
        return NULL;
    }

    if (scanf("%c", &temp) != 1 || temp != ',') {
        ERROR(2);
        return NULL;
    }

    if (scanf("%c", &temp) != 1 || temp != ' ') {
        ERROR(2);
        return NULL;
    }

    if (scanf("%d", &(p->index)) != 1) {
        ERROR(3);
        return NULL;
    }

    ERROR(0);
    return p;
}
void show(const struct student_t* p)
{
    if(p == NULL) return;
    printf("%s %s, %d", p->name, p->surname, p->index);
}
