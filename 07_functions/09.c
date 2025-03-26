#include <stdio.h>


int is_prime(int a);
int is_twin(int a, int b);

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
    
    while(x1<=x2-2){
        if(is_twin(x1,x1+2)==1){
            printf("%d, %d\n",x1,x1+2);
            z++;
        }
        x1++;
    }
    if(z==0){
        printf("Nothing to show");
    }
    
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
int is_twin(int a, int b)
{
    if(b-a==2||a-b==2){
        if(is_prime(a)==1&&is_prime(b)==1)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}
