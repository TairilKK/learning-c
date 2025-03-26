//
// Created by jdobr on 30.12.2021.
//
#include "02_statistics.h"

int bubble_sort(int tab[], int size){
    if(size<1)
        return 1;
    if(size==1){
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
        if(che==0)
            return 0;
    }
    return 0;
}
float median(int tab[], int size){
    if(size<1)
        return 0;
    bubble_sort(tab,size);
    if(size%2)
        return (float)tab[size/2];
    else
        return ((float)tab[size/2]+tab[size/2-1])/2;
}
int mode(int tab[], int size){
    if(size<1)
        return 0;
    if(size==1)
        return tab[0];

    int n=0; int ni=0;
    for(int i=0;i<size;i++) {
        int m=0;
        for (int j = 0; j < size; j++) {
            if(tab[i]==tab[j])
                m++;
        }
        if(m>n){
            n=m;
            ni=i;
        }
        else if(m==n){
            n=m;
            if(tab[i]<tab[ni]){
                ni=i;
            }
        }
    }
    return tab[ni];
}
float average(const int tab[], int size){
    if(size<1)
        return 0;
    int sum=0;
    for(int i=0;i<size;i++)
        sum+=tab[i];
    return (float)sum/size;
}

