#include <stdio.h>
#include <string.h>

int main()
{
    char txt [1001];

    printf("Podaj tekst:\n");
    scanf("%1000[^\n]",txt);

    printf("%ld", strlen(txt));

    return 0;
}