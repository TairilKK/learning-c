#include <stdio.h>
#include <math.h>

int main()
{
    float a, b, c;
    
    printf("Podaj wartoĹÄ a: ");
    scanf("%f", &a);
    
    printf("Podaj wartoĹÄ b: ");
    scanf("%f", &b);
    
    printf("Podaj wartoĹÄ c: ");
    scanf("%f", &c);
    
    
    float skw = a*a + b*b + c*c;
    
    printf("%.2f", sqrt(skw));
    
    
    return 0;
}
