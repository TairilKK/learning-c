#include <stdio.h>
#include <math.h>


int is_prime(unsigned long long);
int length(unsigned long long a);
unsigned long long find_largest_prime_number(unsigned long long number);

int main() {
    unsigned long long n;
    printf("Podaj liczbe:");
    if(scanf("%llu",&n)!=1) {
        printf("Incorrect input");
        return 1;
    }
    unsigned long long a=find_largest_prime_number(n);

    printf("%llu",a);

    return 0;
}
int is_prime(unsigned long long a){
    if(a<2)
        return 0;
    if(a==2)
        return 1;
    for (int i=2; i <= sqrt (a); i++) {
        if (a % i == 0)
            return 0;
    }
    return 1;

}
int length(unsigned long long a){
    int i=0;
    while(a!=0) {
        a/=10;
        i++;
    }
    return i;

}
unsigned long long find_largest_prime_number(unsigned long long number){
    if(is_prime(number)==1)
        return number;
    else if(number<10)
        return 0;

    int len = length(number);
    unsigned long long pr=0;
    unsigned long long n;

    for(int k=len-1;k>=0;k--){
        if(pr!=0)
            return pr;
        for(int i=0;i<len-k+1;i++){
            n=number/((unsigned long long)pow(10,i))%(unsigned long long)pow(10,k);
            if(is_prime(n)==1&&n>pr)
                pr=n;
        }
    }
    return pr;
}

