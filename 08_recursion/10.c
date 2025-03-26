#include <stdio.h>

int is_prime_rec(int, int);
int is_superprime_rec(int);

int main()
{
    int x1;
    printf("Podaj x:");
    if(scanf("%d",&x1)!=1){
        printf("Incorrect input");
        return 1;
    }

    if(is_superprime_rec(x1))
        printf("YES");
    else
        printf("NO");

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
int is_superprime_rec(int x){
    if(x<=0)
        return 0;
    else if(x<10)
        return is_prime_rec(x,x-1);

    if(is_prime_rec(x,x-1)==1)
        return is_superprime_rec(x/10);

    return 0;
}

