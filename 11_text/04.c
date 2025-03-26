#include <stdio.h>

char* change_letter_size(char* dest, const char* src);

int main() {
    char text[1001];
    char destination[1001];
    char *txt=text;
    char *dest=destination;

    printf("Podaj tekst:");
    scanf("%1000[^\n]s",txt);
    while(getchar()!='\n');
    change_letter_size(dest,text);
    printf("%s",dest);

    return 0;
}
char* change_letter_size(char* dest, const char* src){
    if(dest==NULL||src==NULL)
        return NULL;

    for(int i=0;*(src+i)!='\0';i++){
        if(*(src+i)>='a'&&*(src+i)<='z')
            *(dest+i)=*(src+i)-'a'+'A';
        else if(*(src+i)>='A'&&*(src+i)<='Z')
            *(dest+i)=*(src+i)-'A'+'a';
        else
            *(dest+i)=*(src+i);
        *(dest+i+1)='\0';
    }
    return dest;
}

