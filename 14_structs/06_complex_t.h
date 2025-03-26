//
// Created by jdobr on 17.08.2023.
//

#ifndef INC_07_COMPLEX_T_H
#define INC_07_COMPLEX_T_H

#define ERROR(error_value)           \
    do                               \
    {                                \
        if (err_code != NULL)        \
            *err_code = error_value; \
    } while (0)

struct complex_t
{
    float re;
    float im;
};

struct complex_t *set(struct complex_t *cp, float re, float im, int *err_code);
float complex_abs(struct complex_t *cp, int *err_code);
void show(const struct complex_t *cp);

#endif // INC_07_COMPLEX_T_H
