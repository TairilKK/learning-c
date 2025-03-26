#include <stdio.h>

int main()
{
    float tab[10];
    int c=0;
    printf("Podaj liczby:\n");
    for(int i = 0;i<10;i+=2)
        c+=scanf("%f %f",&tab[i],&tab[i+1]);
    
    if(c==10){
        for(int i = 0;i<10;i++)
            printf("%d %f\n",i,tab[i]);
    }
    else{
        printf("Input data type error");
        return 1;
    }
    return 0;
}
