//
// Created by jdobr on 09.08.2023.
//
#include <stdio.h>
#include <stdlib.h>

#include "08_functions.h"

void print_chicken(void){
    printf(" MM\n"
           "<' \\___/|\n"
           "  \\_  _/\n"
           "    ][\n");
}

void print_egg(void){
    printf("  .~~~.\n"
           " /     \\\n"
           "(\\/\\/\\/\\)\n"
           " \\     /\n"
           "  `~~~`\n");
}
void print_rabbit(void){
    printf(" \\\\   //\n"
           "  )\\-/(\n"
           "  /o o\\\n"
           " ( =T= )\n"
           " /'---'\\\n");
}

void (**easter(int size, void (*func0)(void),void (*func1)(void), void (*func2)(void)))(void){
    if(func0 == NULL || func1 == NULL || func2 == NULL || size<1)
        return NULL;

    int ran;

    void (**ret)(void) = calloc(size, sizeof(void(*)(void)));
    if(ret == NULL)
        return NULL;

    for(int i = 0; i < size; ++i) {
        ran = rand() % 3;
        if (ran == 0) *(ret + i) = func0;
        else if (ran == 1) *(ret + i) = func1;
        else *(ret + i) = func2;
    }

    return ret;
}
