#include <stdio.h>

float quadratic_equation(float a, float b, float c, float x);

int main()
{
    float a,b,c,x;
    int c1;
    printf("Podaj rowananie:");
    c1=scanf("%fx^2%fx%f",&a,&b,&c);
    if(c1!=3){
        printf("incorrect input");
        return 1;
    }
    printf("Podaj x: ");
    c1 = scanf("%f",&x);
    if(c1!=1){
        printf("incorrect input");
        return 1;
    }
    printf("Wynik: %f",quadratic_equation(a,b,c,x));

    return 0;
}
float quadratic_equation(float a, float b, float c, float x){
    return a*x*x+b*x+c;
}

