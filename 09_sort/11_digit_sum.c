#include <stdio.h>
#include "05_vector_utils.h"

#define SIZE_VEC 151
#define STOP_VALUE 0

int sort_by_sum(int tab[], int size);
int sum_of_digits(int number);

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
    sort_by_sum(vec,len);
    display_vector(vec,len);

    return 0;
}

int sort_by_sum(int tab[], int size){
    if(size<1)
        return 1;
    if(size==1)
        return 0;

    for(int k=0;k<size;k++) {
        for (int i = 0; i < size - 1-k; i++) {
            if (sum_of_digits(tab[i])> sum_of_digits(tab[i+1])) {
                int ch = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = ch;
            }
            if (sum_of_digits(tab[i]) == sum_of_digits(tab[i+1])&&tab[i]>tab[i+1]){
                int ch = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = ch;
            }
        }
    }
    return 0;
}
int sum_of_digits(int number){
    if(number<0)
        number*=-1;
    if(number==0)
        return 0;
    return number-(number/10*10)+sum_of_digits(number/10);
}
