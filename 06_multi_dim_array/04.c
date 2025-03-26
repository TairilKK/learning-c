#include <stdio.h>

int main()
{
    int c=0,s=0;
    int mac[16][16];
    int macZ[16][16];
    
    printf("podaj liczby:\n");
    for(int w=0;w<15;w++){
        for(int k=0;k<15;k++){
            s++;
            c+=scanf("%d",&mac[w][k]);
            if(c!=s){
                printf("incorrect input");
                return 1;
            }
            else if(!(mac[w][k]>=0&&mac[w][k]<30)){
                printf("value out of range");
                return 2;
            }
        }
    }
    if(c==15*15){
        for(int w=0;w<15;w++){
            for(int k=0;k<15;k++){
                int ile=0;
                int a=mac[w][k];
                for(int w1=0;w1<15;w1++){
                    for(int k1=0;k1<15;k1++){
                        if(mac[w1][k1]==a)
                            ile++;
                        }
                    }
                    macZ[w][k]=ile;
                }
            }
            for(int w=0;w<15;w++){
                for(int k=0;k<15;k++){
                    printf("%d ",macZ[w][k]);
                }
                printf("\n");
            }
    }
    else{
        printf("incorrect input");
        return 1;
    }

    return 0;
}
