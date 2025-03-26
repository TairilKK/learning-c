#include <stdio.h>

float add(float a, float b);

int main()
{
    float a,b;
    int c;
    
    printf("Podaj pierwsza liczbe: ");
    c=scanf("%f",&a);
    if(c!=1){
        printf("incorrect input");
        return 1;
    }
    
    printf("Podaj druga liczbe: ");
    c=scanf("%f",&b);
    if(c!=1){
        printf("incorrect input");
        return 1;
    }
    printf("Wynik: %f",add(a,b));

    return 0;
}
float add(float a, float b){
    return a+b;
}

