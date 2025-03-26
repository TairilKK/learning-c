#include <stdio.h>

int add(int, int);

int main()
{
    int a,b,c;
    
    printf("Podaj pierwsza liczbe: ");
    c=scanf("%d",&a);
    if(c!=1){
        printf("incorrect input");
        return 1;
    }
    
    printf("Podaj druga liczbe: ");
    c=scanf("%d",&b);
    if(c!=1){
        printf("incorrect input");
        return 1;
    }
    printf("Wynik: %d",add(a,b));

    return 0;
}
int add(int a, int b){
    return a+b;
}

