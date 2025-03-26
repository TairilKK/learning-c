//
// Created by jdobr on 03.01.2022.
//
#include <stdio.h>

int read_vector(int *vec, int size, int stop_value){
    int l=0;
    if(vec==NULL)
        return -1;
    for(int* p=vec; p<vec+size; p++)   {
        if(scanf("%d",p)!= 1)
            return -2;
        else if(*p == stop_value)
            return l;
        l++;
    }
    if(l<1)
        return -1;
    else {
        while (getchar() != '\n');
        return l;
    }
}

void display_vector(const int* tab, int size){
    if(size>0){
        for(int* p=(int*)tab;p<tab+size;p++)
            printf("%d ",*p);
        printf("\n");
    }
}
