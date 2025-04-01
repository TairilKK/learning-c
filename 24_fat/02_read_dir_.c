#include <stdio.h>
#include "02_directory_reader.h"

#define SIZE 2

void display_entry_short(struct dir_entry_t d){
    printf("%02d/%02d/%04d ", d.creation_date.day, d.creation_date.month, d.creation_date.year);
    printf("%02d:%02d ", d.creation_time.hour, d.creation_time.minute);
    if(d.is_directory)
        printf("*DIRECTORY*");
    else
        printf("%11lu", d.size);
    putchar(' ');

    printf("%s\n", d.name);
}

int main(void) {
    char input[101], *in;
    struct dir_entry_t *p_dir_entry;
    printf("Podaj sciezke do pliku:");
    if(scanf("%[^\n]100", input) == 0){
        printf("Incorrect input\n");
        return 1;
    }

    in = input;
    while(1){
        p_dir_entry = read_directory_entry(in);
        in = NULL;
        if(p_dir_entry == NULL)
            break;
        display_entry_short(*p_dir_entry);
        free(p_dir_entry);
        p_dir_entry = NULL;
    }
    read_directory_entry(in);

    return 0;
}