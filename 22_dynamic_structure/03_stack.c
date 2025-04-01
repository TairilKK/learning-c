//
// Created by jdobr on 03.08.2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "03_stack.h"

void stack_destroy(struct stack_t** stack){
    if(stack == NULL)
        return;

    struct stack_t * temp = (*stack);
    while(temp != NULL){
        temp = (*stack);
        (*stack) = temp->prev;
        free(temp->sentence);
        free(temp);
        temp = (*stack);
    }
}

char *stack_pop(struct stack_t **stack, int *err_code){
    if(stack == NULL || *stack == NULL) {
        if(err_code != NULL)
            *err_code = 1;
        return NULL;
    }

    char * res = (*stack)->sentence;
    struct stack_t *temp = (*stack)->prev;

    free((*stack));

    *stack = temp;
    if(err_code != NULL)
        *err_code = 0;

    return res;

}


int stack_push(struct stack_t **stack, char *value) {
    if(stack == NULL || value == NULL)
        return 1;

    struct stack_t *newElement = calloc(1, sizeof(struct stack_t));
    if (newElement == NULL)
        return 2;
    newElement->sentence = value;
    newElement->prev = *stack;
    *stack = newElement;
    return 0;
}

int stack_save(const struct stack_t *stack, const char *filename){
    if(stack == NULL || filename == NULL)
        return 1;
    FILE *f = fopen(filename, "w");
    if(f == NULL)
        return 2;

    struct stack_t * temp = (struct stack_t *) stack;
    while(temp != NULL) {
        fprintf(f, "%s", temp->sentence);
        temp = temp->prev;
    }
    fclose(f);
    return 0;
}



int stack_load(struct stack_t **stack, const char *filename) {
    if (stack == NULL || filename == NULL || (*stack) != NULL)
        return 1;

    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return 2;

    char c;
    size_t size = 0;
    long start_position = ftell(f);
    while ((c = fgetc(f)) != EOF) {
        if (c == '.') {
            fseek(f, start_position, SEEK_SET);

            char *sentence = calloc(size + 2, sizeof(char));
            if (sentence == NULL) {
                stack_destroy(stack);
                fclose(f);
                return 3;
            }

            fscanf(f, "%[^.]", sentence);
            *(sentence + size) = '.';

            int error = stack_push(stack, sentence);
            if (error) {
                stack_destroy(stack);
                free(sentence);
                fclose(f);
                return 3;
            }

            size = 0;
            fgetc(f);
            start_position = ftell(f);
        } else {
            size++;
        }
    }

    fclose(f);
    return 0;
}
