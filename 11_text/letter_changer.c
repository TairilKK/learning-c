#include <stdio.h>
#include "letter_changer.h"

char to_lower(char a){
    if(a>='A'&&a<='Z')
        return a-'A'+'a';
    else
        return a;
}
char to_upper(char a){
    if(a>='a'&&a<='z')
        return a-'a'+'A';
    else
        return a;
}
char* change_letter_size(char *txt, enum letter_changer_t c){
    if(txt==NULL)
        return NULL;
    for(char *p=txt;*p!='\0';p++){
        if(c==TO_LOWER)
            *p=to_lower(*p);
        if(c==TO_UPPER)
            *p=to_upper(*p);
    }
    return txt;
}

