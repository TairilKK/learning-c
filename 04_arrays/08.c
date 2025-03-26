#include <stdio.h>

int main()
{
    int tab[10],max, min;
    int c=0;
    float suma=0;
    
    printf("Podaj liczby:\n");
    for(int i = 0;i<10;i+=2){
        c+=scanf("%d %d",&tab[i],&tab[i+1]);
        suma+=(float)tab[i]+(float)tab[i+1];
    }
    if(c==10){
        max=tab[0];
        min=tab[0];
        for(int i=0;i<10;i++){
            if(tab[i]>max) max=tab[i];
            else if(tab[i]<min) min=tab[i];
            
        }
        
        printf("%.4f\n", suma/10.0);
        printf("%d\n", max);
        printf("%d\n", min);
    }
    
    else{
        printf("Input data type error");
        return 1;
    }
    return 0;
}
