//
// Created by jdobr on 17.08.2023.
//
#include <stdio.h>

#include "date_t.h"

void show(const struct date_t* d)
{
    if(d == NULL) return;
    if(d->day<10)
        printf("0");
    printf("%d-", d->day);

    if(d->month<10)
        printf("0");
    printf("%d-", d->month);

    if(d->year<1000)
        printf("0");
    if(d->year<100)
        printf("0");
    if(d->year<10)
        printf("0");

    printf("%d", d->year);
}

int validate(const struct date_t* d)
{
    if(d == NULL) return -1;
    if(d->year < 1 || d->month < 1 || d->month > 12 || d->day < 1) return 0;
    if((d->month == 1 || d->month == 3 || d->month == 5 || d->month == 7 || d->month == 8 || d->month == 10 || d->month == 12) && d->day > 31) return 0;
    if((d->month == 4 || d->month == 6 || d->month == 9 || d->month == 11) && d->day > 30) return 0;
    if(d->month == 2 && is_leap(d->year) == 1 && d->day > 29) return 0;
    if(d->month == 2 && is_leap(d->year) == 0 && d->day > 28) return 0;

    return 1;
}

int is_leap(int d)
{
    if(d % 4 == 0)
    {
        if(d % 100 == 0)
        {
            if(d % 400 == 0)
                return 1;
            return 0;
        }
        return 1;
    }
    return 0;
}


struct date_t* set_date(struct date_t* d, int day, int month, int year, int *err_code)
{
    if(d == NULL){ ERROR(1); return NULL; }
    d->year = year;
    d->month = month;
    d->day = day;
    ERROR(0);
    return d;
}

struct date_t* read(struct date_t* d, int *err_code)
{
    if(d == NULL) {ERROR(1); return NULL;}
    int day, month, year;
    if(scanf("%d-%d-%d",&day, &month, &year) != 3)
    {
        ERROR(2);
        return NULL;
    }
    set_date(d, day, month, year,NULL);
    ERROR(0);
    return d;
}
