#include <stdio.h>

int main()
{
    float a, b;
    
    printf("Wpisz pierwszÄ liczbe: ");
    scanf("%f", &a);
    
    printf("Wpisz drugÄ liczbÄ: ");
    scanf("%f", &b);
    
    printf("%f\n%f\n%f\n%f\n",a+b,a-b,a*b,a/b);
    
    return 0;
}
