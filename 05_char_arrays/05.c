#include <stdio.h>
#include <string.h>


int main()
{
    char name[11];
    printf("Podaj imie:");
    scanf("%10s",name);
    if(name[strlen(name)-1]=='a')
        printf("Imie zenskie");
    else
        printf("Imie meskie");
    
    return 0;
}
