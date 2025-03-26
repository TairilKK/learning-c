#include <stdio.h>
#include <stdlib.h>
#include "05_vector_utils.h"


#define SIZE_VEC 151
#define STOP_VALUE 0

int sort_negative_asc_positive_desc(int tab[], int size);
int bubble_sort_asc(int tab[], int size);
int bubble_sort_desc(int tab[], int size, int from);

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
    sort_negative_asc_positive_desc(vec,len);
    display_vector(vec,len);
    return 0;
}
int sort_negative_asc_positive_desc(int tab[], int size){
    if(size<1)
        return 1;
    bubble_sort_asc(tab,size);

    int i=0;
    while(tab[i]<0&&i<=size){
        i++;
    }
    bubble_sort_desc(tab,size,i);

    return 0;
}
int bubble_sort_asc(int tab[], int size){
    if(size<1)
        return 1;
    if(size==1)
        return 0;

    for(int j=0;j<size;j++) {
        int che=0;
        for (int i = 0; i < size-j-1; i++) {
            if (tab[i] > tab[i + 1]) {
                int ch = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = ch;
                che++;
            }
        }
        if(che==0)
            return 0;
    }
    return 0;
}

int bubble_sort_desc(int tab[], int size, int from){
    if(size<1)
        return 1;
    if(size==1)
        return 0;

    for(int j=0;j<size;j++) {
        int che=0;
        for (int i = from; i < size-j-1; i++) {
            if (tab[i] < tab[i + 1]) {
                int ch = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = ch;
                che++;
            }
        }
        if(che==0)
            return 0;
    }
    return 0;
}
