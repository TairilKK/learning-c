#include <stdio.h>

int main() {

    char c1,c2,c3,c4,c5;

    printf("Podaj 5 liter: ");
    scanf("%c%c%c%c%c",&c1,&c2,&c3,&c4,&c5);

    if(c1<='z' && c1>='a')
    {
        c1+='A'-'a';
    }
    if(c2<='z' && c2>='a')
    {
        c2+='A'-'a';
    }
    if(c3<='z' && c3>='a')
    {
        c3+='A'-'a';
    }
    if(c4<='z' && c4>='a')
    {
        c4+='A'-'a';
    }
    if(c5<='z' && c5>='a')
    {
        c5+='A'-'a';
    }

    printf("%c%c%c%c%c",c1,c2,c3,c4,c5);

    return 0;
}
