#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int read_vector(int vec[], int size, int stop_value);
void display_vector(const int vec[], int size);
void sort(int vec[], int size);
int dlugosc(int);
int por(int a, int b);

#define STOP 0

int main() {
    int tab[1001];

    printf("Podaj liczby:\n");
    int len = read_vector(tab,1000,STOP);
    if(len==-1){
        printf("Not enough data available");
        return 3;
    }
    else if(len==-2){
        printf("Incorrect input");
        return 1;
    }

    sort(tab,len);
    display_vector(tab,len);

    return 0;
}
int read_vector(int vec[], int size, int stop_value){
    int l=0;
    for(int i=0; i<size ;i++)   {
        if(scanf("%d",&vec[i])!= 1|| vec[i]<0|| vec[i]>2000000000)
            return -2;
        else if(i==0 && vec[i] == stop_value)
            return -1;
        else if(vec[i] == stop_value) {
            fflush(stdin);
            return l;
        }
        l++;
    }
    if(l<1)
        return -1;
    else{
        fflush(stdin);
        return l;
    }
}
void display_vector(const int vec[], int size){
    if(size>0){
        for(int i=0;i<size;i++)
            printf("%d",vec[i]);
        printf("\n");
    }
}
void sort(int vec[],int size){
    for(int j=0;j<size-1;j++) {
        for (int i = 0; i < size-1-j; i++) {
            if (por(vec[i], vec[i + 1])) {
                int ch = vec[i];
                vec[i] = vec[i + 1];
                vec[i + 1] = ch;
            }
        }
    }
}
int dlugosc(int a){
    if(a==0)
        return 0;

    return 1+dlugosc(a/10);
}
int por(int a, int b){
    int dl;
    if(dlugosc(a)<dlugosc(b))
        dl=dlugosc(b);
    else
        dl=dlugosc(a);

    int i=1;
    while(i<2*dl+1){
        int Ca,Cb;

        Ca = (a /(int)pow(10, (abs(dlugosc(a)-(i%dlugosc(a)))%dlugosc(a))))%10;
        Cb = (b /(int)pow(10, (abs(dlugosc(b)-(i%dlugosc(b)))%dlugosc(b))))%10;


        if(Ca==Cb)
            i++;
        else if(Ca>Cb)
            return 0;
        else
            return 1;
    }
    return 0;
}