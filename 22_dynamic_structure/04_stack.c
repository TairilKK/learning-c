//
// Created by jdobr on 27.07.2023.
//

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int stack_init(struct stack_t **stack)
{
    if(stack == NULL)
        return 1;

    *stack = (struct stack_t *) calloc(1, sizeof (struct  stack_t));
    if(*stack ==  NULL)
        return 2;

    (*stack)->head = NULL;
    return 0;
}

int stack_push(struct stack_t *stack, int value)
{
    if(stack == NULL)
        return 1;

    struct node_t * newNode = (struct node_t *) calloc(1, sizeof (struct node_t));
    if (newNode == NULL)
        return 2;

    newNode->data = value;
    newNode->next = stack->head;

    stack->head = newNode;

    return 0;
}

int stack_pop(struct stack_t* stack, int *err_code)
{
    if(stack == NULL || stack_empty(stack) != 0)
    {
        ERROR(1);
        return 0;
    }
    struct node_t * temp = stack->head;
    stack->head = temp->next;

    int res = temp->data;
    free(temp);
    ERROR(0);
    return res;
}
int stack_empty(const struct stack_t* stack)
{
    if(stack == NULL)
        return 2;

    if(stack->head == NULL)
        return 1;

    return 0;
}

void stack_destroy(struct stack_t** stack)
{
    if(stack != NULL)
    {
        if(*stack != NULL)
        {
            while((*stack)->head != NULL)
            {
                struct node_t * temp = (*stack)->head;
                (*stack)->head = temp->next;
                free(temp);
            }
            free(*stack);
        }
    }
}

void stack_display(const struct stack_t* stack)
{
    if(stack != NULL)
    {
        struct node_t * temp = stack->head;
        while(temp != NULL)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
    }
}

void stack_display2(const struct stack_t* stack)
{
    if(stack != NULL)
    {
        struct node_t * temp = stack->head;
        int count = 0;
        while(temp != NULL)
        {
            count++;
            temp = temp->next;
        }

        temp = stack->head;
        for (int i = count - 1; i >= 0; i--) {
            struct node_t *temp2 = stack->head;
            for (int j = 0; j < i; j++) {
                temp2 = temp2->next;
            }
            printf("%d ", temp2->data);
        }
    }
}
