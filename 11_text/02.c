#include <stdio.h>

int marks_counter(const char* text, int* uppercase, int* lowercase, int* whitespace);

int main() {
    char text[1001];
    char *txt=text;
    int uppercase, lowercase, whitespace;
    int *uc=&uppercase;
    int *lc=&lowercase;
    int *ws=&whitespace;

    printf("Podaj tekst:");
    scanf("%1000[^\n]s",txt);
    while(getchar()!='\n');

    marks_counter(txt,uc,lc,ws);
    printf("%d\n%d\n%d",*uc,*lc,*ws);

    return 0;
}
int marks_counter(const char* text, int* uppercase, int* lowercase, int* whitespace){
    if(text==NULL || uppercase==NULL || lowercase == NULL || whitespace == NULL)
        return 1;
    int i=0;
    int l=0,u=0,w=0;
    while(*(text+i)!='\0'){
        if(*(text+i)>='a' && *(text+i)<='z')
            l++;
        if(*(text+i)>='A' && *(text+i)<='Z')
            u++;
        if(*(text+i)==' ' || *(text+i)=='\n'||*(text+i)=='\t')
            w++;
        i++;
    }

    *lowercase=l;
    *uppercase=u;
    *whitespace=w;

    return 0;
}

