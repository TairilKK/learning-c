#include <stdio.h>
#include <string.h>

int main()
{
    char string[1001];
    int przes;
    printf("Podaj tekst:\n");
    scanf("%1000[^\n]s",string);
    printf("Podaj znak kodowy:\n");
    int c=scanf("%d",&przes);
    int n='Z'-'A'+1;

    if(c==1){
        for(int i=0;i<(int)strlen(string);i++){

            if(string[i]>='A'&&string[i]<='Z'){
                string[i]+=przes%26;

                if(string[i]>'Z')
                    string[i]-=n;
            }
            else if(string[i]>='a'&&string[i]<='z'){
                string[i]-=n-przes%26;

                if(string[i]<'a')
                    string[i]+=n;
            }
        }
        printf("%s",string);
    }
    else{
        printf("Incorrect input");
        return 1;
    }

    return 0;
}