#include <stdio.h>

#include "date_t.h"

int main() {
    struct date_t a;
    int error;
    printf("Enter a date (formatted as dd-mm-yyyy): ");

    read(&a, &error);
    if(error)
    {
        printf("Incorrect input");
        return 1;
    }
    if(!validate(&a)) { printf("Incorrect"); return 0;}
    printf("Given date: ");
    show(&a);
    printf("\n");
    printf("Correct");

    return 0;
}

