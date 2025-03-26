//
// Created by jdobr on 18.08.2023.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "03_student_t.h"

struct student_t* read(struct student_t* p, int *err_code)
{
    if(p == NULL){ ERROR(1); return NULL; }

    char temp;
    char index_str[20];
    char year_str[20];

    /* NAME */

    if (scanf("%19[^,\n]", p->name) != 1) {
        ERROR(1);
        return NULL;
    }
    if (scanf("%c", &temp) != 1 || temp != ',') {
        ERROR(1);
        return NULL;
    }
    if (scanf("%c", &temp) != 1 || temp != ' ') {
        ERROR(2);
        return NULL;
    }

    /* SURNAME */

    if (scanf("%39[^,\n]", p->surname) != 1) {
        ERROR(2);
        return NULL;
    }
    if (scanf("%c", &temp) != 1 || temp != ',') {
        ERROR(2);
        return NULL;
    }
    if (scanf("%c", &temp) != 1 || temp != ' ') {
        ERROR(3);
        return NULL;
    }

    /* INDEX */

    /* INDEX */

    if (scanf("%19[^,\n]", index_str) != 1) {
        ERROR(3);
        return NULL;
    }
    if (scanf("%c", &temp) != 1 || temp != ',') {
        ERROR(3);
        return NULL;
    }
    p->index = (int) strtol(index_str, NULL, 10);
    if(p->index == 0 && (*index_str != '0' || strlen(index_str) != 1)) {
        ERROR(3);
        return NULL;
    }

    if (scanf("%c", &temp) != 1 || temp != ' ') {
        ERROR(4);
        return NULL;
    }

    /* FIELD */

    if (scanf("%49[^,\n]", p->field) != 1) {
        ERROR(4);
        return NULL;
    }
    if (scanf("%c", &temp) != 1 || temp != ',') {
        ERROR(4);
        return NULL;
    }
    if (scanf("%c", &temp) != 1 || temp != ' ') {
        ERROR(5);
        return NULL;
    }

    /* FACULTY */

    if (scanf("%79[^,\n]", p->faculty) != 1) {
        ERROR(5);
        return NULL;
    }
    if (scanf("%c", &temp) != 1 || temp != ',') {
        ERROR(5);
        return NULL;
    }
    if (scanf("%c", &temp) != 1 || temp != ' ') {
        ERROR(6);
        return NULL;
    }
    /* YEAR */

    if (scanf("%19[^,\n]", year_str) != 1) {
        ERROR(6);
        return NULL;
    }
    p->year = (int)strtol(year_str, NULL, 10);
    if(p->year == 0 && (*year_str != '0' || strlen(year_str) != 1)) {
        ERROR(6);
        return NULL;
    }

    ERROR(0);
    return p;
}

struct student_t* set(struct student_t* student, const char * name,
                      const char * surname, int index,
                      const char * field, const char * faculty,
                      int year, int *err_code)
{
    if(student == NULL || name == NULL || surname == NULL || field == NULL || faculty == NULL || year<1)
    {
        ERROR(1); return NULL;
    }
    if(strlen(name) > 19 || strlen(surname)>39 || strlen(field)>49 ||
            strlen(faculty)>79)
    {
        ERROR(1); return NULL;
    }
    strcpy(student->name, name);
    strcpy(student->surname, surname);
    strcpy(student->field, field);
    strcpy(student->faculty, faculty);
    student->index = index;
    student->year = year;
    ERROR(0);
    return student;

}

void display(const struct student_t* p){
    if(p == NULL) return;
    char vowels[] = "aeiouyAEIOUY";
    int a_an = 0;
    for(int i = 0; i < (int) sizeof(vowels); ++i)
        if(*(p->field + 0) == *(vowels+i))
            a_an++;

    printf("%s %s, index number: %d, was a", p->name, p->surname, p->index);
    if(a_an)
        putchar('n');
    printf(" %s student at the %s in %d.", p->field, p->faculty, p->year);
}

void display_name(const struct student_t* student){
    if(student == NULL) return;
    printf("Student name: %s", student->name);
}
void display_surname(const struct student_t* student){
    if(student == NULL) return;
    printf("Student surname: %s", student->surname);
}
void display_index(const struct student_t* student){
    if(student == NULL) return;
    printf("Index: %d", student->index);
}
void display_field(const struct student_t* student){
    if(student == NULL) return;
    printf("Field: %s", student->field);
}
void display_faculty(const struct student_t* student){
    if(student == NULL) return;
    printf("Faculty: %s", student->faculty);
}
void display_year(const struct student_t* student){
    if(student == NULL) return;
    printf("Year: %d", student->year);
}

