#include <stdio.h>

#include "07_color.h"

#define MAX_COLOR_T_ARRAY_SIZE 100

int main() {
    struct color_t colors[MAX_COLOR_T_ARRAY_SIZE];
    struct color_t unknown;
    int size, err_code;
    char nazwa_zmiennej [31];

    printf("Enter file name: \n");
    if (scanf("%30s", nazwa_zmiennej) != 1) {
        printf("Incorrect input");
        return 1;
    }
    while (getchar() != '\n');

    size = load_colors_t(nazwa_zmiennej, colors, MAX_COLOR_T_ARRAY_SIZE);
    if(size == -2){
        printf("Couldn't open file");
        return 4;
    }
    if(size == -3){
        printf("File corrupted");
        return 6;
    }
    while(1) {
        printf("Enter a color as four values (R, G, B, A): ");
        if (scanf("%hhu %hhu %hhu %hhu", &unknown.r, &unknown.g, &unknown.b, &unknown.a) != 4) {
            printf("Incorrect input");
            return 0;
        }
        unknown.color = find_nearest_neighbour(colors, size, &unknown, &err_code);
        if(unknown.color == RED) printf("RED\n");
        if(unknown.color == GREEN) printf("GREEN\n");
        if(unknown.color == BLUE) printf("BLUE\n");
        if(unknown.color == YELLOW) printf("YELLOW\n");
        if(unknown.color == UNKNOWN) printf("UNKNOWN\n");
    }
}

