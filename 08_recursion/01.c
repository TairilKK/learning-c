#include <stdio.h>

unsigned long factorial_rec(int);

int main()
{
    int n;
    printf("Podaj n:");
    if(scanf("%d",&n)!=1){
        printf("incorrect input");
        return 1;
    }
    
    if(factorial_rec(n)==0){
        printf("Incorrect input data");
        return 2;
    }
    printf("Wynik: %ld",factorial_rec(n));
    return 0;
}

unsigned long factorial_rec(int n){
    if(n<0||n>20)
        return 0;
    else if(n<2)
        return 1;
    return n*factorial_rec(n-1);
}
