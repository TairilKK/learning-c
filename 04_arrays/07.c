#include <stdio.h>

int main()
{
    int tab[10],dziel;
    int c=0;
    
    printf("Podaj liczby:\n");
    for(int i = 0;i<10;i+=2)
        c+=scanf("%d %d",&tab[i],&tab[i+1]);
    
    if(c==10){
        for(int i = 0;i<10;i++){
                dziel = 0;
                for(int j=2;j<tab[i];j++)
                {
                    if(tab[i]%j==0)
                        dziel++;
                }
                if(tab[i]<=1)
                    printf("%d\tother\n",tab[i]);
                else if(dziel==0)
                    printf("%d\tprime\n",tab[i]);
                else
                    printf("%d\tcomposite\n",tab[i]);
            }
        }
    
    else{
        printf("Input data type error");
        return 1;
    }
    return 0;
}
