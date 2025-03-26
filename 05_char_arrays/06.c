#include <stdio.h>
#include <string.h>


int main()
{
    int wyr=0; 
    char txt[1002];
    printf("Podaj tekst:\n");
    scanf("%1000[^\n]s",txt);

    for(int i=0;i<(int)strlen(txt)-1;i++){
        if(txt[i]<'A' || (txt[i]>'Z'&&txt[i]<'a')|| txt[i]>'z'){ 
            if((txt[i-1]>='a'&&txt[i-1]<='z')||(txt[i-1]>='A'&&txt[i-1]<='Z'))
                wyr++;
        }
    }
    printf("%d", wyr+1);
    
    return 0;

}