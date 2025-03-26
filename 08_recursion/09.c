#include <stdio.h>

int is_prime_rec(int, int);
int write_rec(int, int);

int main()
{
    int x1,x2;
    printf("Podaj x1:");
    if(scanf("%d",&x1)!=1){
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj x2:");
    if(scanf("%d",&x2)!=1||x1>x2){
        printf("Incorrect input");
        return 1;
    }
    
    if(write_rec(x1,x2)==0){
        printf("Nothing to show");
        return 2;
    }
    
    return 0;
}
int is_prime_rec(int x, int n){
    if(x<=1)
        return 0;
    if(n<=1)
        return 1;
    if(x%n!=0)
        return is_prime_rec(x,n-1);
    else
        return 0;
}
int write_rec(int x1, int x2){
    if(x1>x2)
        return 0;
    if(is_prime_rec(x1,x1-1)==1){
        printf("%d ",x1);
        return 1+write_rec(x1+1,x2);
    }
    else{
        return 0+write_rec(x1+1,x2);
    }
}
