#include <stdio.h>

char* space_changer(char* txt);

int main() {
    char text[1001];
    char *txt=text;
    printf("Podaj tekst1:");
    scanf("%1000[^\n]s",txt);
    while(getchar()!='\n');

    space_changer(txt);
    printf("%s",txt);
    return 0;
}
char* space_changer(char* txt){
    if(txt==NULL)
        return NULL;
    for(int i=0;*(txt+i)!='\0';i++){
        if(*(txt+i)==' ')
            *(txt+i)='_';
    }
    return txt;
}
