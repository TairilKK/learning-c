#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "04_stack.h"

void pushBitsToStack(uint64_t number, struct stack_t *bitStack) {
    bool foundFirstOne = false;

    for (int i = 63; i >= 0; i--) { // Iterujemy przez bity od najstarszych
        uint64_t mask = 1ULL << i;
        if ((number & mask) != 0) {
            foundFirstOne = true;
        }

        if (foundFirstOne) {
            stack_push(bitStack, (number & mask) != 0);
        }
    }
}

int main() {
    uint64_t input;
    struct stack_t * stack;
    if(stack_init(&stack) != 0)
    {
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Enter number: ");
    if(scanf("%lu", &input) != 1)
    {
        printf("Incorrect input");
        stack_destroy(&stack);
        return 1;
    }
    if(input == 0){
        printf("0");
        stack_destroy(&stack);
        return 0;
    }
    bool foundFirstOne = false;

    for (int i = 63; i >= 0; i--) { // Iterujemy przez bity od najstarszych
        uint64_t mask = 1ULL << i;
        if ((input & mask) != 0) {
            foundFirstOne = true;
        }

        if (foundFirstOne) {
            if(stack_push(stack, (input & mask) != 0)!=0)
            {
                printf("Failed to allocate memory");
                stack_destroy(&stack);
                return 8;
            }
        }
    }

    stack_display2(stack);

    stack_destroy(&stack);
    return 0;
}
