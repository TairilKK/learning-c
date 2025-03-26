//
// Created by jdobr on 17.08.2023.
//

#ifndef INC_08_DATE_T_H
#define INC_08_DATE_T_H

#define ERROR(error_code)           \
    do                              \
    {                               \
        if (err_code != NULL)       \
            *err_code = error_code; \
    } while (0)

struct date_t
{
    int day;
    int month;
    int year;
};

struct date_t *read(struct date_t *d, int *err_code);
struct date_t *set_date(struct date_t *d, int day, int month, int year, int *err_code);

int validate(const struct date_t *d);

void show(const struct date_t *d);

int is_leap(int d);

#endif // INC_08_DATE_T_H
