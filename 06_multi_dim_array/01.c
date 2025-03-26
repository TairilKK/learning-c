#include <stdio.h>

int main()
{
    int c=0;
    int zam;
    int mac[6][6];
    printf("Podaj macierz:\n");
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            c+=scanf("%d", &mac[j][i]);
        }
    }
    if(c==25){
        for(int i=0;i<5;i++){
            zam=mac[i][i];
            mac[i][i]=mac[4-i][i];
            mac[4-i][i]=zam;
        }
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            printf("%d ",mac[j][i]);
        }
        printf("\n");
    }
    }else{
        printf("Incorrect input");
        return 1;
    }
    
    return 0;
}
