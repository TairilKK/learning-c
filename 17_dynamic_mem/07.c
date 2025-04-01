#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_CAPACITY 40

#include "07_image_utils.h"

char * modifyFilename(char * s){
    int size = (int)strlen(s);
    char c0 = *(s + size - 4);
    char c1 = *(s + size - 3);
    char c2 = *(s + size - 2);
    char c3 = *(s + size - 1);

    strcpy(s + size - 4, "_modified");

    size = (int)strlen(s);
    *(s + size + 0) = c0;
    *(s + size + 1) = c1;
    *(s + size + 2) = c2;
    *(s + size + 3) = c3;
    *(s + size + 4) = '\0';


    return s;
}


int main() {

    /* READ FILENAME */
    char * filename = calloc(FILENAME_CAPACITY, sizeof(char));
    if(!filename){
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Enter destination image file name: ");
    int a = 0;
    char c = 0;
    while((c = getchar()) != '\n' && a < (FILENAME_CAPACITY - 1)){
        *(filename + a) = c;
        *(filename + a + 1) = '\0';
        a++;
    }
    if(a == (FILENAME_CAPACITY - 1))
        while (getchar() != '\n');
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

    /* FILE COUNT */
    int count = 0;
    printf("How many subimages you want to draw: ");
    if(scanf(" %d", &count) != 1){
        printf("Incorrect input");
        destroy_image(&img);
        free(filename);
        return 1;
    }
    else if(count < 1){
        printf("Incorrect input data");
        destroy_image(&img);
        free(filename);
        return 2;
    }
    while(getchar() != '\n');

    /* NEW IMG */
    struct image_t * iimg = NULL;
    char * filename1 = calloc(40, sizeof(char));
    if(!filename1){
        printf("Failed to allocate memory");
        destroy_image(&img);
        free(filename);
        return 8;
    }
    int x = 0, y = 0;
    for(int i = 0; i < count; ++i){
        printf("Enter a name of a subimage: ");
        a = 0;
        while((c = getchar()) != '\n' && a < (FILENAME_CAPACITY - 1)){
            *(filename1 + a) = c;
            *(filename1 + a + 1) = '\0';
            a++;
        }
        if(a == (FILENAME_CAPACITY - 1))
            while (getchar() != '\n');

        iimg = load_image_t(filename1, &error);
        if(error == 2)
            printf("Couldn't open file\n");
        else if(error == 3){
            printf("File corrupted\n");
        }
        else if(error == 4){
            printf("Failed to allocate memory");
            free(filename);
            free(filename1);
            return 8;
        }
        else{
            printf("Enter coordinates (x, y): ");
            if(scanf("%d %d", &x, &y) != 2){
                printf("Incorrect input");
                destroy_image(&img);
                destroy_image(&iimg);
                free(filename);
                free(filename1);
                return 1;
            }
            while(getchar() != '\n');

            if(draw_image(img, iimg, x, y) == 1)
                printf("Incorrect input data\n");
        }
        destroy_image(&iimg);
    }

    error = save_image_t(modifyFilename(filename), img);

    if(error == 0) {
        printf("File saved");
        free(filename);
        free(filename1);
        destroy_image(&img);
        return 0;
    }
    else  {
        printf("Couldn't create file");
        free(filename);
        free(filename1);
        destroy_image(&img);
        return 5;
    }
}
