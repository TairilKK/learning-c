#include <stdio.h>
#include "02_vector_utils.h"
#include "02_statistics.h"

#define SIZE_VEC 151
#define STOP_VALUE 0


int main() {
    int vec[SIZE_VEC];
    printf("Podaj wektor:");
    int len=read_vector(vec,SIZE_VEC-1,STOP_VALUE);
    if(len==-1){
        printf("Not enough data available");
        return 3;
    }
    if(len==-2){
        printf("Incorrect input");
        return 1;
    }

    printf("%.2f\n",median(vec,len));
    printf("%d\n",mode(vec,len));
    printf("%.2f\n",average(vec,len));

    return 0;
}

