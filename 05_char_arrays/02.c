#include <stdio.h>

int main()
{
    char name[31];
    
    printf("Jak masz na imie?\n");
    scanf("%30s", name);
    
    printf("Witaj %s!",name);

    return 0;
}