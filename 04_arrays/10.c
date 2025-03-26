#include <stdio.h>

int main()
{
    int i=0,c=0,s=0,tab[100],tabs[100]={0};

    printf("Podaj liczby:\n");
    do{
       c+=scanf("%d",&tab[i]);
       i++;
    }while(tab[i-1]!=-1&&i<100);
    if(c==1){
        printf("not enough data available"); return 2;
    }
    else if(c==i){
        if(c<99){
            for(int j=0;j<i-1;j++){
                tabs[j]=tab[i-2-j];
            }
            for(int j=0;j<i-1;j++){
                if(tabs[j]==tab[j]){
                    s++;
                }
            }
        }
        else{
            for(int j=0;j<100;j++){
                tabs[j]=tab[99-j];
            }
            for(int j=0;j<100;j++){
                if(tabs[j]==tab[j]){
                    s++;
                }
            }
        }
        if(s==i-1||s==100)
            printf("TAK");
        else{
            printf("NIE");
            
        }
    }
    else{
        printf("Incorrect input"); return 1;
    }
    
    
    return 0;
}