#include <stdio.h>

char * my_strpbrk ( const char *, const char * );

int main() {
    char text[1001];
    char *txt=text;
    char vowel[]="AaEeIiOoUuYy";
    char *vow=vowel;

    printf("Podaj tekst:");
    fgets(txt,1001,stdin);

    my_strpbrk(txt,vow);

    int licz=0;
    char *pch = my_strpbrk (txt, vow);
    while (pch != NULL){
        licz++;
        pch = my_strpbrk (pch+1,vow);
    }
    printf ("%d",licz);

    return 0;
}
char * my_strpbrk ( const char *txt, const char *v ){
    if(v==NULL || txt ==NULL)
        return 0;
    int i=0,j;
    while(*(txt+i)!='\0'){
        j=0;
        while(*(v+j)!='\0'){
            if(*(txt+i)==*(v+j))
                return (char*)(txt+i);
            j++;
        }
        i++;
    }
    return NULL;
}
