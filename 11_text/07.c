#include <stdio.h>
#include "letter_changer.h"

int main() {

    char txt[1001];
    char *t1=txt;
    char change;

    printf("Podaj tekst:\n");
    scanf("%1000[^\n]c",t1);
    while(getchar()!='\n');

    printf("Jesli wielkie wcisnij: B, male: S\n");
    change = getchar();
    while (getchar() != '\n');
    char i='.';
    while(i=='.'){
        if(change=='B'||change=='b'||change=='S'||change=='s')
            i='>';
        else {
            printf("Incorrect input\nJesli wielkie wcisnij: B, male: S\n");
            change = getchar();
            while (getchar() != '\n');
        }
    }
    if(change=='b'||change=='B')
        change_letter_size(t1,TO_UPPER);
    else
        change_letter_size(t1,TO_LOWER);


    printf("%s",t1);

    return 0;
}

