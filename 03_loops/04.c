#include <stdio.h>

int main()
{
    float a, S=0;
    printf("Podaj 10 liczb:\n");
    int c =0;
    int i = 0;
    while(i<10)
    {
        c=scanf("%f", &a);
        if(c==1)
        {
            if(a<0) S-=a;
            else S+=a;
        }
        else
        {
            printf("Incorrect input");
            return 1;
        }
        i++;
    }
    printf("%.2f",S);

    return 0;
}
