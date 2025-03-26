#include <stdio.h>

#include "03_student_t.h"

int main() {
    int err1 = 0;
    int err = 0;
    struct student_t me, in;

    printf("Podaj dane: ");
    read(&in, &err1);
    if(err1!= 0){printf("Incorrect input");}
    else display(&in);
    putchar('\n');
    set(&me, "Jakub", "Dobrosielski", 240651, "informatyka", "weiia", 2023, &err);
    display(&me);

    if(err1 == 0) {
        putchar('\n');
        display_name(&in);
        putchar('\n');
        display_surname(&in);
        putchar('\n');
        display_index(&in);
        putchar('\n');
        display_field(&in);
        putchar('\n');
        display_faculty(&in);
        putchar('\n');
        display_year(&in);
        putchar('\n');
    }

    return err1;
}

