#include <stdio.h>
#include <stdlib.h>

#include "08_image_utils.h"

#define FILENAME_CAPACITY 40

int main() {

    /* READ FILENAME */
    char * filename = calloc(FILENAME_CAPACITY, sizeof(char));
    if(!filename){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj nazwe: ");
    int a = 0;
    char c = 0;
    while((c = getchar()) != '\n' && a < (FILENAME_CAPACITY - 1)) {
        *(filename + a) = c;
        *(filename + a + 1) = '\0';
        a++;
    }
    if(c != '\n')
        while(getchar() != '\n');

    /* LOAD IMAGE */
    int error = 0;
    struct image_t * img = load_image_t(filename, &error);
    if(error == 2){
        printf("Couldn't open file");
        free(filename);
        return 4;
    }
    else if(error == 3){
        printf("File corrupted");
        free(filename);
        return 6;
    }
    else if(error == 4){
        printf("Failed to allocate memory");
        free(filename);
        return 8;
    }

    /* READ RECTANGLE */
    struct rectangle_t rect = {{0, 0}, 0, 0};
    printf("Podaj wspolrzedne i wymiary prostokata: ");
    if(scanf("%d %d %d %d", &(rect.p.x), &(rect.p.y), &(rect.width), &(rect.height)) != 4){
        printf("Incorrect input");
        destroy_image(&img);
        free(filename);
        return 1;
    }

    /* READ COLOR */
    int value;
    printf("Podaj kolor: ");
    if(scanf("%d", &value) != 1){
        printf("Incorrect input");
        destroy_image(&img);
        free(filename);
        return 1;
    }

    /* DRAW RECTANGLE */
    error = image_draw_rectangle(img, &rect, value);
    if(error == 1){
        printf("Incorrect input data");
        destroy_image(&img);
        free(filename);
        return 2;
    }

    /* SAVE IMG */
    error = save_image_t(filename, img);
    if(error == 0) {
        printf("File saved");
        free(filename);
        destroy_image(&img);
        return 0;
    }
    else  {
        printf("Couldn't create file");
        free(filename);
        destroy_image(&img);
        return 5;
    }
}
