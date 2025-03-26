#include <stdio.h>

int add(const char* number1, const char* number2, char* result, int size);
int validate(const char * number);
int len(char*);
void reverse(char*);

int main() {
    char numbera[201],numberb[201],result[202];
    char *a=numbera,*b=numberb,*res=result;
    printf("Podaj pierwsza liczbe:");
    scanf("%200[^\n]s",a);
    while(getchar()!='\n');

    printf("Podaj druga liczbe:");
    scanf("%200[^\n]s",b);
    while(getchar()!='\n');

    if(add(a,b,res,201)==1){
        printf("Incorrect input");
        return 1;
    }

    printf("%s",res);

    return 0;
}
int validate(const char * number){
    if(number==NULL)
        return -1;
    if(*number=='0'&&*(number+1)>='0'&&*(number+1)<=':'-1)
        return 0;
    for(char* p=(char*)number;*p!='\0';p++){
        if(*p<'0'||*p>=':')
            return 0;
    }
    return 1;
}
int add(const char* number1, const char* number2, char* result, int size){
    if(number1==NULL|| number2==NULL||result==NULL||size<1)
        return 1;

    *(result+size-1)='\0';

    if(!(validate(number1)&&validate(number2)))
        return 1;


    int a=len((char*)number1);
    int b=len((char*)number2);

    if(size<=a && size<=b)
        return 2;


    int i=0, j=0;

    while((*(number1+i)!='\0'||*(number2+i)!='\0')&&i<size){
        char n1=*(number1+a-i-1)-'0';
        char n2=*(number2+b-i-1)-'0';

        if(a-1-i<0||n1<0||n1>':'-1-'0')
            n1=0;

        if(b-1-i<0||n2<0||n2>':'-1-'0')
            n2=0;

        j+=n1+n2;
        *(result+i)=(j%10)+'0';
        *(result+i+1)='\0';

        j/=10;
        i++;
    }
    if(j!=0){
        *(result+i)=(j%10)+'0';
        *(result+i+1)='\0';
    }

    reverse(result);
    int licz=0;
    if(validate(result)==0){
        for(char *p=result;*p!='\0';p++) {
            *p = *(p + 1);
            licz++;
        }
        *(result+licz)='\0';
    }

    if(*(result+size-1)!='\0')
        return 2;
    return 0;
}
int len(char* a){
    if(a==NULL)
        return -1;
    int i=0;
    while(*a!='\0'){
        a++;
        i++;
    }
    return i;
}
void reverse(char *a) {
    if(a==NULL)
        return;
    int l = len(a);
    for(int i=0; i<l/2; i++) {
        char temp = *(a+l-i-1);
        *(a+l-i-1) = *(a+i);
        *(a+i) = temp;
    }
}











