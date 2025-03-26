#include <stdio.h>
#include "vector_utils.h"

int sort(int* tab, int size);


#define SIZE_VEC 101
#define STOP_VALUE (-1)

int main() {
   int T[SIZE_VEC];

   printf("Podaj liczby:");
   int len=read_vector(T,SIZE_VEC-1,STOP_VALUE);
   if(len==-1){
       printf("Not enough data available");
       return 3;
   }
   if(len==-2){
        printf("Incorrect input");
       return 1;
   }
    if(*T==STOP_VALUE){
        printf("Not enough data available");
        return 3;
    }
    sort(T,len);
    display_vector(T,len);


    return 0;
}
int sort(int* tab, int size){
    if(tab==NULL)
        return 1;
    if(size<1)
        return 1;
    if(size==1)
        return 0;
    for(int* j=tab;j<tab+size;j++) {
        int che=0;
        for (int* i=tab;i<tab-1+size;i++) {
            if (*i > *(i+1)) {
                int ch = *i;
                *i = *(i+1);
                *(i+1) = ch;
                che++;
            }
        }
        if(che==0)
            return 0;
    }
    return 0;
}


