#include <stdio.h>

long power_rec(int a, int n);

int main()
{
    int a,n;
    printf("podaj a:");
    if(scanf("%d", &a)!=1){
        printf("incorrect input");
        return 1;
    }
    printf("podaj n:");
    if(scanf("%d", &n)!=1){
        printf("incorrect input");
        return 1;
    }
    else if(n<0){
        printf("Incorrect input data");
        return 2;
    }
    printf("Wynik: %ld",power_rec(a,n));

    return 0;
}

long power_rec(int a, int n){
    if(n<0||a==0)
        return 0;
    if(a==1||n==0)
        return 1;
    if(n==1)
        return a;
        
    return a*power_rec(a,n-1);
}
