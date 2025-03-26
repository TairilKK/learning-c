#include <stdio.h>

#include "figure.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    struct figure_t data[50] = {0};
    int temp, size=0;

    while(size < 50){
        printf("Enter figure's type: ");
        if(scanf(" %d", &temp) != 1){
            printf("Incorrect input");
            return 1;
        }
        if(temp == 0) {
            if(sort_by_area_(data, size) == 1) {
                printf("Incorrect input data");
                return 2;
            }
            for (int i = 0; i < size && i < 50;printf("\n"), ++i)
                display_figure((data+i));
            return 0;
        }
        else if(temp == (int)TRIANGLE) {
            printf("Enter vertices' coordinates of a triangle (x1 y1 x2 y2 x3 y3):");
            if (scanf(" %d %d %d %d %d %d", &(data+size)->triangle.p1.x, &(data+size)->triangle.p1.y,
                      &(data+size)->triangle.p2.x, &(data+size)->triangle.p2.y,
                      &(data+size)->triangle.p3.x, &(data+size)->triangle.p3.y ) != 6) {
                printf("Incorrect input");
                return 1;
            }
            (data+size)->type = TRIANGLE;
            size++;
        }
        else if(temp == (int)RECTANGLE) {
            printf("Enter coordinates of a rectangle along with its dimensions (x y width height): ");
            if (scanf(" %d %d %d %d", &(data+size)->rect.p.x, &(data+size)->rect.p.y,
            &(data+size)->rect.width, &(data+size)->rect.height) != 4) {
                printf("Incorrect input");
                return 1;
            }
            (data+size)->type = RECTANGLE;
            size++;
        }
        else if(temp == (int)CIRCLE) {
            printf("Enter coordinates and radius of a circle: ");
            if (scanf(" %d %d %f", &(data+size)->circ.c.x, &(data+size)->circ.c.y, &(data+size)->circ.r) != 3) {
                printf("Incorrect input");
                return 1;
            }
            (data+size)->type = CIRCLE;
            size++;
        }
        else {
            printf("Incorrect input data");
            return 2;
        }
    }

    if(sort_by_area_(data, size) == 1) {
        printf("Incorrect input data");
        return 2;
    }
    for (int i = 0; i < size && i < 50;printf("\n"), ++i)
        display_figure((data+i));
    return 0;
}


