#include <stdio.h>

int main()
{
    int a, b, blad; char op;

    printf("Podaj pierwsza liczbe:");
    int c =scanf("%d", &a);

    printf("Podaj pierwsza liczbe:");
    c+=scanf("%d", &b);

    printf("Podaj symbol operacji:");
    scanf("%*c%c", &op);

    if(op == '+' || op == '*' || op == '-' || op == '/') c=c+1;

    if(c==3)
    {
        if (op == '+')
        {
            printf("%d",a+b);
            blad = 0;
        }
        if (op == '*')
        {
            printf("%d",a*b);
            blad = 0;
        }
        if (op == '-')
        {
            printf("%d",a-b);
            blad = 0;
        }
        if (op == '/')
        {
            if(b==0)
            {
                printf("Operation not permitted");
                blad = 2;
            }
            else printf("%.2f",(float)a/b);
        }
    }
    else
    {
        blad = 1;
        printf("Incorrect input");
    }




    return blad;
}
