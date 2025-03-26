#include <stdio.h>

int main() {
    int n;
    printf("Podaj liczbe:");

    if(scanf("%d", &n)!=1||n<0||n==1){
        printf("Incorrect input");
        return 1;
    }
    int m=1;

    while(n%m==0){
        n++;
        m++;
    }
    m--;
    printf("%d",m);


    return 0;
}
