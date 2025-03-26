#include <stdio.h>
#include <string.h>

int main()
{
    char wyr[51];
    int wyn=0;
    
    printf("Podaj wyrazenie nawiasowe:");
    scanf("%50s", wyr);
    
    for(int i=0;i<(int)strlen(wyr);i++){
        if(wyr[i]=='(')
            wyn++;
        if(wyr[i]==')')
            wyn--;
        if(wyn<0){
            printf("Niepoprawny");
            return 0;
        }
    }
    if(wyn==0)
        printf("Poprawny");
    else
        printf("Niepoprawny");
    
    return 0;
}

