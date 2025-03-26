#include <stdio.h>
#include "05_vector_utils.h"

#define SIZE_VEC 151
#define STOP_VALUE -1

int freq(int number, int tab[], int size);
int freq_sort(int tab[], int size);

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
    freq_sort(vec,len);
    display_vector(vec,len);

    return 0;
}
int freq(int number,int tab[],int size){
    if(size<1)
        return -1;

    int f=0;
    for(int i=0;i<size;i++){
        if(number==tab[i])
            f++;
    }
    return f;
}
int freq_sort(int tab[], int size){
    if(size<1)
        return 1;
    if(size==1)
        return 0;

    for(int k=0;k<size;k++) {
        for (int i = 0; i < size - 1-k; i++) {
            if (freq(tab[i],tab,size) < freq(tab[i+1],tab,size)) {
                int ch = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = ch;
            }
            if (freq(tab[i],tab,size)== freq(tab[i+1],tab,size)&&tab[i]>tab[i+1]){
                int ch = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = ch;
            }
        }
    }
    return 0;
}

