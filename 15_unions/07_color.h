//
// Created by jdobr on 20.08.2023.
//

#ifndef INC_08_COLOR_H
#define INC_08_COLOR_H

#define ERROR(error_code)           \
    do                              \
    {                               \
        if (err_code)               \
            *err_code = error_code; \
    } while (0)

enum colors
{
    RED = 1,
    GREEN,
    BLUE,
    YELLOW,
    UNKNOWN
};

struct color_t
{
    union
    {
        unsigned int value;
        struct
        {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
        };
    };
    enum colors color;
};

int load_colors_t(const char *filename, struct color_t *p, int N);
float distance(const struct color_t *p1, const struct color_t *p2, int *err_code);
enum colors find_nearest_neighbour(const struct color_t *database, int size,
                                   const struct color_t *unknown, int *err_code);

#endif // INC_08_COLOR_H
