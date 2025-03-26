#include <stdio.h>

int main() {
    float a,b; int c;

    printf("Podaj a:");
    c=scanf("%f",&a);
    if(c==0)
    {
        printf("Incorrect input");
        return 1;
    }

    printf("Podaj b:");
    c=scanf("%f",&b);
    if(c==0)
    {
        printf("Incorrect input");
        return 1;
    }
        if((a+b)*(a-b)==a*a+b*b) printf("tozsamosc jest prawdziwa");
        else printf("tozsamosc nie jest prawdziwa");

    return 0;
}
