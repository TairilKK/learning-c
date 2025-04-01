#include <stdio.h>
#include <stdlib.h>
#include "03_stack.h"

int main(int argc, char ** argv) {
    if(argc <= 1) {
        printf("Not enough arguments");
        return 9;
    }
    struct stack_t * stack;
    int res;
    for (int i = 1; i < argc; i++){
        res = stack_load(&stack, *(argv + i));
        if(res == 0){
            res = stack_save(stack, *(argv + i));
            if(res == 2){
                printf("Couldn't create file");
                stack_destroy(&stack);
                return 5;
            }
            printf("File %s saved\n", *(argv + i));
            stack_destroy(&stack);
        }
        else if(res == 2) {
            printf("Couldn't open file %s\n", *(argv + i));
        }
        else if(res == 3){
            printf("Failed to allocate memory");
            return 8;
        }
    }
    stack_destroy(&stack);
    return 0;
}
