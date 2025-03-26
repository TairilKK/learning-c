#include <stdio.h>
#include <string.h>

int main()
{
    int wyn=0;
    int tab[12]={0};
    char string[1001];

    printf("Podaj tekst: ");
    scanf("%1000[^\n]s", string);

    for(int i=0; i<(int)strlen(string); i++){
        if(string[i]=='a')   tab[0]=1;
        else if(string[i]=='A')  tab[1]=1;
        else if(string[i]=='e')  tab[2]=1;
        else if(string[i]=='E')  tab[3]=1;
        else if(string[i]=='i')  tab[4]=1;
        else if(string[i]=='I')  tab[5]=1;
        else if(string[i]=='o')  tab[6]=1;
        else if(string[i]=='O')  tab[7]=1;
        else if(string[i]=='u')  tab[8]=1;
        else if(string[i]=='U')  tab[9]=1;
        else if(string[i]=='y')  tab[10]=1;
        else if(string[i]=='Y')  tab[11]=1;
    }
    for(int i=0;i<12;i++)
        wyn+=tab[i];
    printf("%d", wyn);

    return 0;
}