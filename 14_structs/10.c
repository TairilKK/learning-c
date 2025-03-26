#include <stdio.h>

#include "10_entry_t.h"

#define ENTRY_CAPACITY 10

int main() {
    struct entry_t p[ENTRY_CAPACITY];
    char filename[101];
    char last_name[101];
    printf("Enter file name: ");
    scanf("%100[^\n]", filename);
    while (getchar()!='\n');

    int res = load_phonebook_t(filename, p, ENTRY_CAPACITY);
    if(res == -2)
    {
        printf("Couldn't open file");
        return 4;
    }
    if(res == 0)
    {
        printf("File corrupted");
        return 6;
    }

    printf("Enter last name: ");
    scanf("%100[^\n]", last_name);
    while (getchar()!='\n');
    //for(int i = 0; i<ENTRY_CAPACITY; display(p+i), i++);
    const struct entry_t * result = find_by_last_name(p, res, last_name);
    if(result == NULL) printf("Couldn't find name");
    else display(result);

    return 0;
}

