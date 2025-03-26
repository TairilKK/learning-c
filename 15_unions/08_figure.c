//
// Created by jdobr on 20.08.2023.
//
#include <stdio.h>
#include <math.h>

#include "08_figure.h"

/* DISPLAY */

void display_point(const struct point_t p){
    printf("(%d, %d)",p.x,p.y);
}

void display_rectangle(const struct rectangle_t *rect){
    if(!rect) return;
    printf("Rectangle ");
    display_point(rect->p);
    printf(" , width = %d, height = %d", rect->width, rect->height);
}

void display_triangle(const struct triangle_t *t){
    if(!t) return;
    printf("Triangle ");
    printf("p1");
    display_point(t->p1);
    printf(", p2");
    display_point(t->p2);
    printf(", p3");
    display_point(t->p3);
}

void display_circle(const struct circle_t *circ){
    if(!circ) return;
    printf("Circle ");
    display_point(circ->c);
    printf(", radius = %f", circ->r);
}

void display_figure(struct figure_t *f){
    if(!f) return;
    if(f->type == RECTANGLE) display_rectangle(&(f->rect));
    else if(f->type == TRIANGLE) display_triangle(&(f->triangle));
    else if(f->type == CIRCLE) display_circle(&(f->circ));
}

/* AREA */

float area_triangle(const struct triangle_t *t)
{
    if(!t || ((t->p1.x == t->p2.x) && (t->p1.y == t->p2.y)) || ((t->p1.x == t->p3.x) && (t->p1.y == t->p3.y)) || ((t->p3.x == t->p2.x) && (t->p3.y == t->p2.y)) || ((t->p1.x == t->p2.x) && (t->p1.x == t->p3.x)) || ((t->p1.y == t->p2.y) && (t->p1.y == t->p3.y))) return -1;
    float area = ((float)t->p1.x * ((float)t->p2.y - (float)t->p3.y) +
            (float)t->p2.x * ((float)t->p3.y - (float)t->p1.y) +
            (float)t->p3.x * ((float)t->p1.y - (float)t->p2.y))/2;
    return area < 0 ? -area : area;
}
float area_rectangle(const struct rectangle_t *r){
    if(!r || r->height <= 0 || r->width <= 0) return -1;
    return (float)(r->height) * (float)(r->width);
}
float area_circle(const struct circle_t *c){
    if(!c || c->r <=0) return -1;
    return M_PI * c->r * c->r;
}
float area_figure(const struct figure_t *f){
    if(!f || !f->type) return -1;
    if(f->type == RECTANGLE) return area_rectangle(&(f->rect));
    else if(f->type == TRIANGLE) return area_triangle(&(f->triangle));
    else if(f->type == CIRCLE) return area_circle(&(f->circ));
    return -1;
}


int sort_by_area(struct figure_t **figures, int size){
    if(!figures || size < 1) return 1;

    struct figure_t *temp;
    float area0, area1;
    for(int j = 0; j < size - 1; ++j) {
        for (int i = 0; i < size - 1 - j; ++i) {
            area0 = area_figure(*(figures + i));
            if(area0 == -1)
                return 1;

            area1 = area_figure(*(figures + i + 1));
            if(area1 == -1)
                return 1;

            if(area0 < area1){
                temp = *(figures + i);
                *(figures + i) = *(figures + i + 1);
                *(figures + i + 1) = temp;
            }
        }
    }

    return 0;
}

int sort_by_area_(struct figure_t *figures, int size){
    if(!figures || size < 1) return 1;

    struct figure_t temp;
    float area0, area1;
    for(int j = 0; j < size - 1; ++j) {
        for (int i = 0; i < size - 1 - j; ++i) {
            area0 = area_figure((figures+i));
            if(area0 == -1)
                return 1;

            area1 = area_figure(figures+i + 1);
            if(area1 == -1)
                return 1;

            if(area0 < area1){
                temp = *(figures+i);
                *(figures+i) = *(figures+i+1);
                *(figures+i+1) = temp;
            }
        }
    }

    return 0;
}
