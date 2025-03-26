#include <stdio.h>

int main()
{
    int a, Sp=0, Sn=0;
    printf("Podaj liczby:\n");
    int c =0;
    do
    {
        c=scanf("%d", &a);
        if(c==1)
        {
            if(a%2!=0)
            {
                if(a!=-1)   Sn+=a;
            }
            else Sp+=a;
        }
        else
        {
            printf("Incorrect input");
            return 1;
        }
    }
    while(a!=-1);
    printf("Suma liczb parzystych: %d\n",Sp);
    printf("Suma liczb nieparzystych: %d\n",Sn);

    return 0;
}
