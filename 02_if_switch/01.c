#include <stdio.h>

int main()
{
    int a, b, z;
    printf("Podaj dwie liczby caĹkowite oddzielone spacjÄ: ");
    int c = scanf("%d %d", &a, &b);
    
    if(c==2)
    {
        printf("%d",a+b);
        z=0;
    }
    else
    {
        printf("Incorrect input");
        z=1;
    }

    return z;
}
