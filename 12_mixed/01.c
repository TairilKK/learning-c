#include <stdio.h>

void wypisz(int a,char b);
int dlugosc(long long int a);

int main() {
    long long int a,b;
    printf("Podaj liczbe pierwsza:");
    if(scanf("%lld",&a)!=1){
        printf("Incorrect input");
        return 1;
    }

    printf("Podaj liczbe druga:");
    if(scanf("%lld",&b)!=1){
        printf("Incorrect input");
        return 1;
    }
    int od=dlugosc(a*b);
//Liczba 1
    wypisz(od- dlugosc(a),' ');
    printf("%lld\n",a);
//Liczba 2
    wypisz(od- dlugosc(b),' ');
    printf("%lld\n",b);
//Kreska
    wypisz(od,'-');
    printf("\n");
    long long int b1=b;
    for(int i=0; i < dlugosc((int)b);i++){
        long long int a1=a;
        a1*=b1%10;
        b1/=10;
        if(a1==0)
            wypisz(od- dlugosc(a1)-1-i,' ');
        else
            wypisz(od- dlugosc(a1)-i,' ');
        printf("%lld\n",a1);
    }
//Wynik
    wypisz(od,'-');
    printf("\n");
    printf("%lld",a*b);


    return 0;
}

void wypisz(int a,char b){
    for(int i=0;i<a;i++)
        printf("%c",b);
}

int dlugosc(long long int a){
    if(a==0)
        return 0;

    return 1+dlugosc(a/10);
}
