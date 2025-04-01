//
// Created by jdobr on 09.08.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "char_operations.h"

char lower_to_upper(char ch){
    if(ch>='a' && ch<='z')
        ch = ch - 'a'+'A';
    return ch;
}
char upper_to_lower(char ch){
    if(ch>='A' && ch<='Z')
        ch = ch - 'A'+'a';
    return ch;
}
char space_to_dash(char ch){
    if(ch == ' ')
        ch = '_';
    return ch;
}
char reverse_letter(char ch){
    if(ch>='a' && ch<='z')
        ch = 'z'- (ch - 'a');
    else if(ch>='A' && ch<='Z')
        ch = 'Z'- (ch - 'A');

    return ch;
}

char * letter_modifier(const char * inputText, char (*func)(char)){
    if(inputText == NULL || func == NULL || strlen(inputText) < 1)
        return NULL;

    char * res = calloc(strlen(inputText) + 1, sizeof(char));
    if(res == NULL)
        return NULL;

    for(int i = 0; *(inputText + i) != '\0' ;*(res+i) = func((char)*(inputText + i)), ++i);

    return res;
}