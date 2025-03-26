#include <stdio.h>


int is_prime(int a);

int main()
{
    int x1,x2;
    int c=0;
    int z=0;
    printf("Podaj x1:");
    c=scanf("%d",&x1);
    if(c!=1){
        printf("incorrect input");
        return 1;
    }
    
    printf("Podaj x2:");
    c=scanf("%d",&x2);
    if(c!=1||x1>x2){
        printf("incorrect input");
        return 1;
    }
    
    while(x1<x2+1){
        if(is_prime(x1)==1){
            printf("%d ",x1);
            z++;
        }
        x1++;
    }
    if(z==0)
        printf("Nothing to show");
    
    return 0;
}

int is_prime(int a){
    int ile=0;
    if(a==2)
        return 1;
    else if(a%2==0||a<2)
        return 0;
    for(int i=3;i<a;i+=2){
        if(a%i==0)
            ile++;
    }
    if(ile==0)
        return 1;
    else
        return 0;
}















