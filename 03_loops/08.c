#include <stdio.h>

int main()
{
    float a = 5;
    float b = 3;
  
    printf("%f %f\n",a ,b);
    
    printf("%f \n%.2f \n%f \n%f \n", a*b, (float)a/b, a+b, a-b);
    
    return 0;
}
