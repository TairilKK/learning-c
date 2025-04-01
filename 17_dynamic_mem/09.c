#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "09_image_utils.h"

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

    /* LOAD IMG */
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

    char * filename_s = calloc(FILENAME_CAPACITY + 9, sizeof(char));
    if(!filename_s){
        printf("Failed to allocate memory");
        destroy_image(&img);
        free(filename);
        return 8;
    }

    strcpy(filename_s, "mirror_h_");
    strcat(filename_s, filename);
    struct image_t * img_t = image_flip_horizontal(img);
    if(!img_t){
        printf("Failed to allocate memory");
        destroy_image(&img);
        free(filename);
        free(filename_s);
        return 8;
    }
    if(save_image_t(filename_s,img_t) == 0)
        printf("File saved\n");
    else
        printf("Couldn't create file\n");

    destroy_image(&img_t);

    strcpy(filename_s, "mirror_v_");
    strcat(filename_s, filename);
    img_t = image_flip_vertical(img);
    if(!img_t){
        printf("Failed to allocate memory");
        destroy_image(&img);
        free(filename);
        free(filename_s);
        return 8;
    }
    if(save_image_t(filename_s,img_t) == 0)
        printf("File saved\n");
    else
        printf("Couldn't create file\n");

    destroy_image(&img_t);

    strcpy(filename_s, "invert_");
    strcat(filename_s, filename);
    img_t = image_negate(img);
    if(!img_t){
        printf("Failed to allocate memory");
        destroy_image(&img);
        free(filename);
        free(filename_s);
        return 8;
    }
    if(save_image_t(filename_s,img_t) == 0)
        printf("File saved\n");
    else
        printf("Couldn't create file\n");


    destroy_image(&img_t);
    destroy_image(&img);
    free(filename);
    free(filename_s);

    return 0;
}
