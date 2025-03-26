#include <stdio.h>

int sum_of_digits(long long number);

int main()
{
    long long n;
    printf("Podaj n:");
    if(scanf("%lld",&n)!=1){
        printf("incorrect input");
        return 1;
    }
    printf("Wynik: %d",sum_of_digits(n));

    return 0;
}
int sum_of_digits(long long number){
    if(number<0)
        number*=-1;
    if(number==0)
        return 0;
    return number-(number/10*10)+sum_of_digits(number/10);
}
