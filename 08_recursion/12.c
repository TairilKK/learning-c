#include <stdio.h>

void rectangular_triangle(int n);
void star(int);

int main()
{
    int n;
    printf("Podaj liczbe:");
    if(scanf("%d",&n)!=1){
        printf("Incorrect input");
        return 1;
    }
    if(n<=0){
        printf("Incorrect input data");
        return 2;
    }
    rectangular_triangle(n);

    return 0;
}
void rectangular_triangle(int n){
    if(n<=0){
        return;
    }
    else{
        rectangular_triangle(n-1);
        star(n);
    }
}
void star(int n){
    if(n<=0)
        printf("\n");
    else{
        printf("* ");
        star(n-1);
    }
}
