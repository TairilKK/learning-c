//
// Created by jdobr on 20.08.2023.
//

#ifndef INC_10_FIGURE_H
#define INC_10_FIGURE_H

#define TPOINT(val) display_point(t->p##val);

struct point_t
{
    int x;
    int y;
};

struct rectangle_t
{
    struct point_t p;
    int width;
    int height;
};

struct circle_t
{
    struct point_t c;
    float r;
};

struct triangle_t
{
    struct point_t p1;
    struct point_t p2;
    struct point_t p3;
};

enum figure_types{
    TRIANGLE = 1,
    RECTANGLE,
    CIRCLE
};

struct figure_t{
    union
    {
        struct rectangle_t rect;
        struct triangle_t triangle;
        struct circle_t circ;
    };
    enum figure_types type;
};


float area_triangle(const struct triangle_t *t);
float area_rectangle(const struct rectangle_t *r);
float area_circle(const struct circle_t *c);
float area_figure(const struct figure_t *f);

void display_rectangle(const struct rectangle_t *rect);
void display_triangle(const struct triangle_t *t);
void display_circle(const struct circle_t *circ);
void display_figure(struct figure_t *f);
void display_point(const struct point_t p);

int sort_by_area(struct figure_t **figures, int size);
int sort_by_area_(struct figure_t *figures, int size);
#endif //INC_10_FIGURE_H
