#include <stdio.h>

#include "02_student_t.h"

int main() {
    int err = 0;
    struct student_t p = {"", "", 0};
    printf("Podaj dane:\n");
    if(read(&p, &err) == NULL) { printf("Incorrect input"); return err;}
    show(&p);
    return 0;
}

