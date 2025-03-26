#include <stdio.h>
#include "05_vector_utils.h"

#define SIZE_VEC 151
#define STOP_VALUE 0

int sort_odd_desc(int tab[], int size);
int sort_even_asc(int tab[], int size);


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

    sort_odd_desc(vec,len);
    sort_even_asc(vec,len);
    display_vector(vec,len);

    return 0;
}
int sort_odd_desc(int tab[], int size){
    if(size<1)
        return 1;
    if(size==1)
        return 0;

    for(int k=0;k<size;k++) {
        for (int i = 1; i < size - 1-k; i+=2) {
                if (tab[i] <= tab[i+2]&&i+2<size) {
                    int ch = tab[i];
                    tab[i] = tab[i+2];
                    tab[i+2] = ch;
                }

            }
        }
    return 0;
}

int sort_even_asc(int tab[], int size){
    if(size<1)
        return 1;
    if(size==1)
        return 0;

    for(int k=0;k<size;k+=2) {
        for (int i = 0; i < size - 1-k; i+=2) {
            if (tab[i] >= tab[i+2]&&i+2<size) {
                int ch = tab[i];
                tab[i] = tab[i+2];
                tab[i+2] = ch;
            }

        }
    }
    return 0;
}

