#include <stdio.h>

int main()
{
    int a = 90-64;
    char tab[26];
    
    for(int i=0;i<a;i++)
        tab[i]=i+65;
    
    for(int i=0;i<a;i++)
        printf("%d %c %c\n",tab[i],tab[i],tab[i]+32);

    return 0;
}
