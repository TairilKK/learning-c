#include <stdio.h>

int connect(const char* t1, const char* t2, const char* t3, char* t4, int size);

int main() {
    char a[1001],b[1001],c[1001];
    char d[3003];
    char *t1=a,*t2=b,*t3=c;
    char *t4=d;

    printf("Podaj tekst:\n");
    scanf("%1000[^\n]c",t1);
    while(getchar()!='\n');

    printf("Podaj tekst:\n");
    scanf("%1000[^\n]c",t2);
    while(getchar()!='\n');

    printf("Podaj tekst:\n");
    scanf("%1000[^\n]c",t3);
    while(getchar()!='\n');

    connect(t1,t2,t3,t4,3002);

    printf("%s",t4);
    return 0;
}
int connect(const char* t1, const char* t2, const char* t3, char* t4, int size){
    if(t1==NULL||t2==NULL||t3==NULL||t4==NULL||size<1)
        return 1;

    int i=0;
    while(*(t1+i)!='\0'&&i<size) {
        *(t4 + i) = *(t1 + i);
        i++;
    }
    *(t4+i)=' ';
    i++;
    int j=0;
    while(*(t2+j)!='\0'&&i<size) {
        *(t4 + i) = *(t2 + j);
        i++;
        j++;
    }
    *(t4+i)=' ';
    i++;
    j=0;
    while(*(t3+j)!='\0'&&i<size) {
        *(t4 + i) = *(t3 + j);
        i++;
        j++;
    }
    *(t4+i)='\0';
    if(size<=i)
        return 1;
    return 0;
}
