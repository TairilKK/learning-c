#include <stdio.h>
#include "05_vector_utils.h"

#define SIZE_VEC 151
#define STOP_VALUE 0

int sort_negative_asc_positive_desc(int tab[], int size);
int sort_negative_asc(int tab[], int size);
int sort_positive_desc(int tab[], int size);


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
    if(size==1)
        return 0;

    sort_positive_desc(tab, size);
    sort_negative_asc(tab, size);

    return 0;
}

int sort_negative_asc(int tab[], int size){
    if(size<1)
        return 1;
    if(size==1)
        return 0;

    for(int k=0;k<size;k++) {
        for (int i = 0; i < size - 1-k; i++) {
            if (tab[i] < 0) {
                int j = i + 1;
                while (j < size-k && tab[j] >= 0)
                    j++;
                if (tab[i] >= tab[j]&&j<size) {
                    int ch = tab[i];
                    tab[i] = tab[j];
                    tab[j] = ch;
                }

            }
        }
    }

    return 0;
}
int sort_positive_desc(int tab[], int size){
    if(size<1)
        return 1;
    if(size==1)
        return 0;
    for(int k=0;k<size;k++) {
        for (int i = 0; i < size - 1-k; i++) {
            if (tab[i] >= 0) {
                int j = i + 1;
                while (j < size-k && tab[j] < 0)
                    j++;
                if (tab[i] <= tab[j]&&j<size) {
                    int ch = tab[i];
                    tab[i] = tab[j];
                    tab[j] = ch;
                }

            }
        }
    }

    return 0;
}
