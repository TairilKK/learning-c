#include <stdio.h>
#include "vector_utils.h"

int find_min(const int* tab, int size, int *min);


#define SIZE_VEC 101
#define STOP_VALUE (-1)

int main() {
   int T[SIZE_VEC];
   int mininmum;
   int *min = &mininmum;

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
    find_min(T,len,min);
    printf("Min: %d", *min);
    return 0;
}
int find_min(const int* tab, int size, int *min){
    if(tab==NULL || min==NULL)
        return 1;
    if(size<1)
        return 1;

    *min = *tab;
    for(int* i = (int*)tab;i<tab+size;i++){
        if(*i<*min)
            *min=*i;
    }
    return 0;
}


