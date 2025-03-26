#include <stdio.h>

int main() {

    int n=0;
    char c1,c2,c3,c4,c5;

    printf("Podaj 5 znakow: ");
    int c = scanf("%c%c%c%c%c",&c1,&c2,&c3,&c4,&c5);

    if(c==5)
    {
        if(c1=='x'||c1=='y'||c1=='z'||c1=='2'||c1=='7')
        {
            n++;
        }
        if(c2=='x'||c2=='y'||c2=='z'||c2=='2'||c2=='7')
        {
            n++;
        }
        if(c3=='x'||c3=='y'||c3=='z'||c3=='2'||c3=='7')
        {
            n++;
        }
        if(c4=='x'||c4=='y'||c4=='z'||c4=='2'||c4=='7')
        {
            n++;
        }
        if(c5=='x'||c5=='y'||c5=='z'||c5=='2'||c5=='7')
        {
            n++;
        }
        printf("Szukane znaki wystapily %d raz(y)",n);
    }
    else printf("Incorrect input");

    return 0;
}
