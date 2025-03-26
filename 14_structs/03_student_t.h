//
// Created by jdobr on 18.08.2023.
//

#ifndef INC_03_STUDENT_T_H
#define INC_03_STUDENT_T_H

#define ERROR(error_code)           \
    do                              \
    {                               \
        if (err_code != NULL)       \
            *err_code = error_code; \
    } while (0)

struct student_t
{
    char name[20];
    char surname[40];
    int index;
    char field[50];
    char faculty[80];
    int year;
};

struct student_t *read(struct student_t *p, int *err_code);
struct student_t *set(struct student_t *student, const char *name,
                      const char *surname, int index,
                      const char *field, const char *faculty,
                      int year, int *err_code);

void display(const struct student_t *p);

void display_name(const struct student_t *student);
void display_surname(const struct student_t *student);
void display_index(const struct student_t *student);
void display_field(const struct student_t *student);
void display_faculty(const struct student_t *student);
void display_year(const struct student_t *student);

int my_size(int a);

#endif // INC_03_STUDENT_T_H
