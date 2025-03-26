//
// Created by jdobr on 29.12.2021.
//
#include <stdio.h>

int read_vector(int vec[], int size, int stop_value){
    int l=0;
    for(int i=0; i<size ;i++)   {
        if(scanf("%d",&vec[i])!= 1)
            return -2;
        else if(i==0 && vec[i] == stop_value)
            return -1;
        else if(vec[i] == stop_value)
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
