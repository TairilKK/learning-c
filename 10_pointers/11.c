#include <stdio.h>
#include "vector_utils.h"

int reverse_vector(int* tab, int size);

#define SIZE_VEC 101
#define STOP_VALUE 0

int main() {
   int T[SIZE_VEC];

   printf("Podaj liczby:");
   int len=read_vector(T,SIZE_VEC-1,STOP_VALUE);
   if(len==-1){
       printf("Not enough data available");
       return 3;
   }
   else if(len==-2){
        printf("Incorrect input");
       return 1;
   }
    if(*T==STOP_VALUE){
        printf("Not enough data available");
        return 3;
    }
    display_vector(T,len);

    reverse_vector(T, len);

    display_vector(T,len);

    return 0;
}

int reverse_vector(int* tab, int size){
    if(tab==NULL)
        return 1;
    if(size<1)
        return 1;
    for(int* i = (int*)tab;i<tab+(size/2);i++){
        int ch = *i;
        *i = *(tab+size-(i-tab+1));
        *(tab+size-(i-tab+1))=ch;
    }
    return 0;
}


