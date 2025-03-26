#include <stdio.h>

int starts_with(const char* txt, const char* find);
int ends_with(const char* txt, const char* find);
int clean(char);

int main()
{
    char text[101];
    char *txt=text;
    char find[101];
    char *fnd=find;
    
    printf("Podaj tekst:\n");
    scanf("%100[^\n]s",txt);
    
    clean('\n');
    
    printf("Podaj drugi tekst:\n");
    scanf("%100[^\n]s",fnd);
    
    clean('\n');
    
    printf("%d\n",starts_with(txt,fnd));
    printf("%d",ends_with(txt,fnd));
    
    return 0;
}
int starts_with(const char* txt, const char* find){
    if(txt == NULL|| find == NULL)
        return -1;
    if(*find=='\0')
        return 1;
    if(*txt=='\0')
        return 0;
    if(*txt==*find)
        return starts_with(txt+1,find+1);
    return 0;
    
}
int ends_with(const char* txt, const char* find){
    if(txt == NULL|| find == NULL)
        return -1;
        
    if(*txt==*find&&*(txt+1)!='\0'&&*(find+1)=='\0')
            return 0;
    if(*txt==*find&&*(txt+1)=='\0'&&*(find+1)=='\0')
            return 1;
    if(*txt==*find){
        return ends_with(txt+1,find+1);
    }
    if(*txt=='\0')
        return 0;
        
    return ends_with(txt+1,find);
        
}
int clean(char a){
    if(getchar()!=a)
        return clean(a);
    return 1;
}







