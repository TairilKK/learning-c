#include <stdio.h>

int main()
{
    int tab[10];
    int c=0;
    printf("Podaj liczby:\n");
    for(int i = 0;i<10;i+=2)
        c+=scanf("%d %d",&tab[i],&tab[i+1]);
    
    if(c==10){
        for(int i = 0;i<10;i++){
            if(tab[i]%2==0)
                printf("%d\teven\n",tab[i]);
            else
                printf("%d\todd\n",tab[i]);
        }
    }
    else{
        printf("Input data type error");
        return 1;
    }
    return 0;
}
