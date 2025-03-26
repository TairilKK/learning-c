#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846
float circumference(float);

int main()
{
    float fi;
    printf("Podaj srednice kola:");
    int c=scanf("%f",&fi);
    if(c!=1||fi<=0){
        printf("Incorrect input");
        return 1;
    }
    printf("%f",circumference(fi));
    return 0;
}

float circumference(float a){
    if(a>0)
        return a*PI;
    else
        return -1;
}

