#include <stdio.h>

#include "02_stack.h"

int main() {
    int operation, value, error;
    struct stack_t * stack;
    int res = stack_init(&stack);

    if(res == 2) {
        printf("Failed to allocate memory");
        return 8;
    }

    while(1){
        printf("Co chcesz zrobic? ");

        if(scanf("%d", &operation) != 1){
            printf("Incorrect input");
            stack_destroy(&stack);
            return 1;
        }
        if(operation == 0){
            stack_destroy(&stack);
            return 0;
        }
        else if(operation == 1){
            printf("Podaj liczbe: ");
            if(scanf("%d", &value) != 1){
                printf("Incorrect input");
                stack_destroy(&stack);
                return 1;
            }
            if(stack_push(stack, value) == 2){
                printf("Failed to allocate memory");
                stack_destroy(&stack);
                return 8;
            }
        }
        else if(operation == 2){
            res = stack_pop(stack, &error);
            if(error == 1)
                printf("Stack is empty\n");
            else
                printf("%d\n", res);
        }
        else if(operation == 3){
            printf("%d\n", stack_empty(stack));
        }
        else if(operation == 4){
            if(stack_empty(stack))
                printf("Stack is empty");
            stack_display(stack);
            printf("\n");
        }
        else
            printf("Incorrect input data\n");
    }
    return 0;
}
