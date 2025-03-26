#include <stdio.h>

int main()
{
    int n=0,c=0,tab[101],max, min,suma=0;

    printf("Podaj liczby:\n");
    do{
        c+=scanf("%d",&tab[n]);
        n++;
    }while(tab[n-1]!=-1&&n<101);

    if(c!=n){
        printf("Incorrect input");
        return 1;
    }
    c--;
    max=min=tab[0];
    for(int i=0;i<c;i++){
        suma+=tab[i];
        if(tab[i]>max)
            max=tab[i];
        if(tab[i]<min)
            min=tab[i];
    }
    printf("%d\n%d\n%d\n%.2f\n%d",c ,min, max, (float)suma/(float)c,suma);



    return 0;
}