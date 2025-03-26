#include <stdio.h>

unsigned long sum_rec(int n);

int main()
{
    int n;
    printf("Podaj liczbÄ, dla ktĂłrej chcesz policzyÄ sumÄ:");
    if(scanf("%d",&n)!=1){
        printf("Incorrect input");
        return 1;
    }
    if(sum_rec(n)==0){
        printf("Incorrect input data");
        return 2;
    }
    printf("Wynik: %lu",sum_rec(n));
    return 0;
}
unsigned long sum_rec(int n){
    if(n<1)
        return 0;
    if(n==1)
        return 1;
    return n+sum_rec(n-1);
}
