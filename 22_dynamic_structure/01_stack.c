//
// Created by jdobr on 25.07.2023.
//
#include "01_stack.h"
#include <stdio.h>
#include <stdlib.h>

int stack_init(struct stack_t **stack, int N){
    if(stack == NULL || N<1)
        return 1;

    *stack = (struct stack_t *) calloc(1, sizeof(struct stack_t));

    if(*stack == NULL)
        return 2;

    (*stack)->data = (int *) calloc(N, sizeof(int));

    if((*stack)->data == NULL) {
        free(*stack);
        *stack = NULL;
        return 2;
    }
    (*stack)->head = 0;
    (*stack)->capacity = N;

    return 0;
}

int stack_push(struct stack_t *stack, int value){
    if(stack == NULL || stack->data == NULL || stack->capacity < 1 || stack->head < 0 || stack->capacity < stack->head)
        return 1;
    if(stack->head == stack->capacity){
        int * tData = realloc(stack->data, 2 * stack->capacity * sizeof(int));
        if(tData == NULL)
            return 2;
        stack->data = tData;
        stack->capacity *= 2;
    }
    *(stack->data + stack->head) = value;
    stack->head += 1;
    return 0;
}

int stack_pop(struct stack_t* stack, int *err_code){
    if(stack == NULL){
        if(err_code != NULL) *err_code = 1;
        return 0;
    }
    if(stack->data == NULL || stack->capacity < 1 || stack->head < 0 || stack->capacity < stack->head){
        if(err_code != NULL) *err_code = 1;
        return 0;
    }

    if(stack->capacity == 0 || stack->head == 0){
        if(err_code != NULL) *err_code = 2;
        return 0;
    }

    stack->head -= 1;

    if(err_code != NULL) *err_code = 0;

    return *(stack->data + stack->head);
}

void stack_free(struct stack_t* stack){
    if (stack != NULL) {
        if (stack->data != NULL) {
            free(stack->data);
        }
        free(stack);
    }
}

void stack_display(const struct stack_t* stack){
    if(stack == NULL)
        return;
    if(stack->data == NULL || stack->head < 1 || stack->capacity < 1 || stack->head>stack->capacity)
        return;
    for(int i = stack->head; i > 0; --i, printf("%d ", *(stack->data + i)));
}
