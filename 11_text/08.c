#include <stdio.h>

int message_compression(char* txt);

int main()
{
    char text[1001];
    char *txt=text;
    
    printf("Podaj tekst:\n");
    scanf("%1000[^\n]s",txt);
    while(getchar()!='\n');
    
    message_compression(txt);
    if(*txt=='\0')
        puts("NothingToShow");
    else
        puts(txt);
    
    return 0;
}
int message_compression(char* txt){
    if(txt==NULL)
        return -1;
    int licz=0;
    int i=0;
    
                
    while(*(txt+i)!='\0'){
        if(*(txt+i)>='A'&&*(txt+i)<='Z')
            *(txt+i)-='A'-'a';
        i++;
    }
    if(*(txt)>='a'&&*(txt)<='z')
                *(txt)+='A'-'a';
    i=0;
    while(*(txt+i)!='\0'){
        if(!((*(txt+i)>='a'&&*(txt+i)<='z')||(*(txt+i)>='A'&&*(txt+i)<='Z'))){
            licz++;
            if(*(txt+i+1)>='a'&&*(txt+i+1)<='z')
                *(txt+i+1)+='A'-'a';
            
            for(int k=i;*(txt+k)!='\0';k++)
                *(txt+k)=*(txt+k+1);
            
            i--;
        }
        
        i++;
      
    }
    return licz;
}






