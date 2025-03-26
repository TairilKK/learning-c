#include <stdio.h>
#include <math.h>

int lznacz(int a);

int main() {
    int a;
    printf("Podaj poczatek:");
    if(scanf("%d",&a)!=1) {
        printf("Incorrect input");
        return 1;
    }
    int b;
    printf("Podaj koniec:");
    if(scanf("%d",&b)!=1) {
        printf("Incorrect input");
        return 1;
    }
    if(b<a){
        printf("Incorrect input data");
        return 2;
    }
    int w=0;
    for(int i=a;i<b;i++)
        if(lznacz(i))
            w++;

    printf("%d", w);

    return 0;
}
int lznacz(int a){
    int sum=0;
    int ile=0;

    for (int i=1; i <a; i++) {
        if (a % i == 0) {
            sum += i;
            ile++;
        }
    }
    if((float)sum/(float)ile<sqrt(a))
        return 1;
    return 0;
}
