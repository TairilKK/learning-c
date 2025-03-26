#include <stdio.h>
#include <math.h>

int main()
{
    float x, res;
    
    printf("podaj liczbe: ");
    scanf("%f", &x);
    
    res = 2 * pow(x,3) - 4 * pow(x,2) + 3 * x - 7;
    
    printf("wartoĹÄ funkcji y=%f", res);
    return 0;
}
