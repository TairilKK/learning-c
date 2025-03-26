#include <stdio.h>
#include "01_vector_utils.h"


int bubble_sort(int tab[], int size);

#define STOP_VALUE 0

int main() {
    int vec[151];

    //WCZYTYWANIE WEKTORA
    printf("Podaj wektor:\n");
    int c=read_vector(vec,150,STOP_VALUE);
    //sprawdzannie poprawnego inputu
    if(c==-2){
        printf("Incorrect input");
        return 1;
    }
    if(c<1){
        printf("Not enough data available");
        return 3;
    }
    //sprawdzanie dĹugosci
    bubble_sort(vec,c);

    return 0;
}
int bubble_sort(int tab[], int size){
    if(size<1)
        return 1;
    if(size==1){
        display_vector(tab,size);
        return 0;
    }

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
        display_vector(tab, size);
        if(che==0)
            return 0;
    }
    return 0;
}
