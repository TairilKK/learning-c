#include <stdio.h>
#include "06_array.h"


int main( )
{
    struct array_t ptr;
    struct array_t *a=&ptr;
    int n;

    printf("Podaj liczbe elementow tablicy:");
    if(scanf("%d",&n)!=1){
        printf("Incorrect input\n");
        return 1;
    }
    if(n<1){
        printf("Incorrect input data\n");
        return 2;
    }
    int err = array_create(a,n);
    if(err==2){
        printf("Failed to allocate memory\n");
        return 8;
    }
    int value=1;
    printf("Podaj liczby do zapisania:");
    while(value!=0){
        if(scanf("%d",&value)!=1){
            array_destroy(a);
            printf("Incorrect input\n");
            return 1;
        }
        err=array_push_back(a,value);
        if(err==2){
            printf("Buffer is full\n");
            a->size++;
            break;
        }
    }
    a->size--;
    if(a->size==0)
        printf("Buffer is empty\n");
    else
        array_display(a);

    array_destroy(a);
    return 0;
}
