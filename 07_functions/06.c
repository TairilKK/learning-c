#include <stdio.h>

float poly(float);

int main()
{
    float x;
    printf("Podaj x: ");
    int c = scanf("%f",&x);
    if(c!=1){
        printf("incorrect input");
        return 1;
    }
    printf("Wynik: %f",poly(x));

    return 0;
}
float poly(float x){
    return 5*x*x+12.55*x+0.75;
}

