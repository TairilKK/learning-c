#include <stdio.h>

#define SIZE_V 151
#define STOP_V 0

int read_vector(int vec[], int size, int stop_value);
int is_growing(const int arr[],int n);
int binary_search(const int arr[], int l, int r, int x);

int main()
{
    //ZMIENNE
    int vec[SIZE_V];
    int n;
    int l;
    //WCZYTYWANIE
    
    printf("Podaj wektor:");
    l=read_vector(vec,SIZE_V,STOP_V);
    if(l==-1){//ZA KRĂTKI WEKTOR
        printf("Not enough data available");
        return 3;
    }
    else if(l==-2){//NIEPOPRAWNY INPUT
        printf("Incorrect input");
        return 1;
    }
    
    
    printf("Szukany element:");
    if(scanf("%d",&n)==0||n==0){
        printf("Incorrect input");
        return 1;
    }
    //SPRAWDZANIE CZY ROĹNIE
    if(is_growing(vec,l-1)==-1){
        printf("Incorrect input data");
        return 2;
    }
    printf("%d",binary_search(vec,0,l,n));
    
    return 0;
}


int binary_search(const int arr[], int l, int r, int x){
    if(l==r)
        return -r-1;
    if(arr[l]==x)
        return 0;
    else
        return 1+binary_search(arr,l+1,r,x);
}


int is_growing(const int arr[],int n){
    if(n<1)
        return 0;
    
    if(arr[n-1]<=arr[n])
        return 0+is_growing(arr,n-1);
    else
        return -1;
}

int read_vector(int vec[], int size, int stop_value){
    int l=0;
    for(int i=0; i<size ;i++){
        if(scanf("%d",&vec[i])!= 1)
            return -2;
        else if(i==0 && vec[i] == stop_value)
            return -1;
        else if(vec[i] == stop_value){
            while(getchar()!='\n');
            return l;
        }
        l++;
    }
    if(l<1)
        return -1;
    else{
        while(getchar()!='\n');
        return l;
    }
}


