#include <stdio.h>

int my_strlen(const char* str);
char* my_strcat(char* dest, const char* src);
char* my_strcpy(char* dest, const char* src);

int main() {
    char text[2002];
    char text2[2002];
    char *txt=text;
    char *txt2=text2;


    printf("Podaj tekst1:");
    scanf("%1000[^\n]s",txt);
    while(getchar()!='\n');
    printf("Podaj tekst2:");
    scanf("%1000[^\n]s",txt2);
    while(getchar()!='\n');


   printf("%d %d\n", my_strlen(txt), my_strlen(txt2));
   my_strcat(txt2,txt);
   printf("%s\n",txt2);
   my_strcpy(txt2,txt);
   printf("%s",txt2);


    return 0;
}
int my_strlen(const char* str){
    if(str==NULL)
        return -1;
    int licz=0;
    while(*(str+licz)!='\0')
        licz++;
    return licz;
}
char* my_strcat(char* dest, const char* src){
    if(src==NULL||dest==NULL)
        return NULL;


    int len = my_strlen(dest);
    int i =0;
    while(*(src+i)!='\0') {
        *(dest + len + i) = *(src + i);
        i++;
    }
    *(dest+len+i)='\0';
    return dest;
}
char* my_strcpy(char* dest, const char* src){
    if(src==NULL||dest==NULL)
        return NULL;

    int lens = my_strlen(src);
    for(int i = 0;i<lens;i++){
        *(dest+i)=*(src+i);
    }
    *(dest+lens)='\0';
    return dest;
}
