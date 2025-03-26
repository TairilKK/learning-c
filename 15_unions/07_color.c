//
// Created by jdobr on 20.08.2023.
//
#include <stdio.h>
#include <math.h>

#include "07_color.h"

int load_colors_t(const char *filename, struct color_t* p, int N){
    if(filename == NULL || p == NULL || N < 1) return -1;

    FILE *f = fopen(filename, "r");
    if(f == NULL) return -2;

    char t;
    int counter = 0;

    while(feof(f) || counter<N){
        if(fscanf(f, "%u %u", &((p+counter)->value), &((p+counter)->color))!=2){
            fclose(f);
            return -3;
        }
        t = (char)fgetc(f);
        if(t == EOF || t == '\n') {
            if ((p + counter)->color < 1 || (p + counter)->color > 4){
                fclose(f);
                return -3;
            }
            counter++;
            if(t == EOF) {
                fclose(f);
                return counter;
            }
        }
        else{
            fclose(f);
            return -3;
        }
    }
    fclose(f);
    return counter;
}


float distance(const struct color_t* p1, const struct color_t* p2, int *err_code){
    if(!p1 || !p2) { ERROR(1); return -1;}
    ERROR(0);
    return (float)sqrt(pow(p2->r - p1->r, 2) + pow(p2->g - p1->g, 2) + pow(p2->b - p1->b, 2));
}

enum colors find_nearest_neighbour(const struct color_t* database, int size,
                                   const struct color_t* unknown, int *err_code){

    if(!database || !unknown || size<1){ ERROR(1); return UNKNOWN;}
    int flag = 0;
    float min_distance = distance(database, unknown, NULL), temp;
    struct color_t * color_with_min_distance = (struct color_t *) database;

    for(int i = 0; i < size; ++i){
        temp = distance((database + i), unknown, NULL);
        if(temp < min_distance){
            min_distance = temp;
            color_with_min_distance = (struct color_t *)(database + i);
            flag = 0;
        }
        if(temp == min_distance && color_with_min_distance->color != (database + i)->color){
            flag = 1;
        }
    }
    if(flag == 1) {
        ERROR(2);
        return UNKNOWN;
    }
    ERROR(0);
    return color_with_min_distance->color;
}
