#include <stdio.h>

int GCD(int a, int b);

int main()
{
    int a,b;
    
    printf("Podaj a:");
    if(scanf("%d",&a)!=1){
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj b:");
    if(scanf("%d",&b)!=1){
        printf("Incorrect input");
        return 1;
    }
    printf("Wynik: %d",GCD(a,b));
    return 0;
}
int GCD(int a, int b){
    if(a<0)
        a*=-1;
    if(b<0)
        b*=-1;
    if(b!=0)
    	return GCD(b,a%b);
	
    return a;
}
