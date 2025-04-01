#include <stdio.h>
#include <stdlib.h>

int **create_array_2d(int width, int height);
void display_array_2d(int **ptr, int width, int height);
void destroy_array_2d(int **ptr, int height);

int main() {

    printf("Podaj szerokocs i wysokosc:");
    int w,h;
    if(scanf("%d %d",&w,&h)!=2){
        printf("Incorrect input");
        return 1;
    }
    if(w<1||h<1){
        printf("Incorrect input data");
        return 2;
    }
    int **ptr= create_array_2d(w,h);
    if(ptr==NULL){
        destroy_array_2d(ptr,h);
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby:");
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++)
            if(scanf("%d",(*(ptr+i)+j))!=1){
                destroy_array_2d(ptr,h);
                printf("Incorrect input");
                return 1;
            }
    }
    display_array_2d(ptr,w,h);

    destroy_array_2d(ptr,h);
    return 0;
}

void destroy_array_2d(int **ptr, int height){
    if(ptr==NULL)
        return;
    for (int i = 0; i < height; i++)
        free(*(ptr + i));
    free(ptr);
}
void display_array_2d(int **ptr, int width, int height){
    if(ptr==NULL||width<1||height<1)
        return;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            printf("%d ", *(*(ptr + i)+j));
        printf("\n");
    }
}
int **create_array_2d(int width, int height){
    if(width<1||height<1)
        return NULL;
    int **ptr = malloc(height*sizeof(int*));
    if(ptr==NULL)
        return NULL;
    for(int i=0;i<height;i++){
        *(ptr+i) = malloc(width*sizeof(int));
        if(*(ptr+i)==NULL){
            destroy_array_2d(ptr,i);
            return NULL;
        }

    }
    return ptr;
}