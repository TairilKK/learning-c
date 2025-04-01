//
// Created by jdobr on 14.08.2023.
//
#include <stdio.h>
#include <stdlib.h>

#include "07_doubly_linked_list.h"

struct doubly_linked_list_t* dll_create(){
    struct doubly_linked_list_t * newDll = (struct doubly_linked_list_t *)calloc(1, sizeof (struct doubly_linked_list_t));
    if(newDll != NULL){
        newDll->tail = NULL;
        newDll->head = NULL;
    }

    return newDll;
}

void dll_clear(struct doubly_linked_list_t* dll){
    if(dll == NULL) return;

    struct node_t * temp = dll->head;
    while(temp != NULL)
    {
        dll->head = temp->next;
        free(temp);
        temp = dll->head;
    }
    dll->head = NULL;
    dll->tail = NULL;
}

void dll_destroy(struct doubly_linked_list_t* dll){
    if(dll == NULL) return;
    dll_clear(dll);
    free(dll);
}


int dll_size(const struct doubly_linked_list_t* dll){
    if(dll == NULL)
        return -1;
    int counter = 0;
    struct node_t * temp = dll->head;
    if(temp == NULL)
        return counter;

    while(temp != NULL){
        temp = temp->next;
        counter++;
    }
    return counter;

}
int dll_is_empty(const struct doubly_linked_list_t* dll){
    if(dll == NULL)
        return -1;
    return dll->head == NULL ? 1 : 0;
}

void dll_display(const struct doubly_linked_list_t* dll){
    if(dll == NULL) return;
    struct node_t * temp = dll->head;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
}
void dll_display_reverse(const struct doubly_linked_list_t* dll){
    if(dll == NULL) return;
    struct node_t * temp = dll->tail;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->prev;
    }
}


int dll_push_back(struct doubly_linked_list_t* dll, int value){
    if(dll == NULL) return 1;

    struct node_t * newNode = (struct node_t *)calloc(1, sizeof (struct node_t));
    if(newNode == NULL) return 2;

    if(dll_is_empty(dll))
        dll->head = newNode;

    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = dll->tail;
    if(dll->tail != NULL)
        dll->tail->next = newNode;
    dll->tail = newNode;

    return 0;
}

int dll_concat_zip(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2){
    if (dll1 == NULL || dll2 == NULL) return 1;

    if (dll_is_empty(dll2)) return 0;

    if (dll_is_empty(dll1)) {
        dll1->head = dll2->head;
        dll1->tail = dll2->tail;
        dll2->head = NULL;
        dll2->tail = NULL;
        return 0;
    }

    struct node_t * iterator1 = dll1->head;
    struct node_t * iterator2 = dll2->head;

    while (iterator1 && iterator2) {
        struct node_t* temp1_next = iterator1->next;
        struct node_t* temp2_next = iterator2->next;

        iterator1->next = iterator2;
        iterator2->prev = iterator1;

        if (temp1_next) {
            iterator2->next = temp1_next;
            temp1_next->prev = iterator2;
        } else {
            while(iterator2) {
                dll1->tail = iterator2;
                iterator2 = iterator2->next;
            }
            break;
        }

        iterator1 = temp1_next;
        iterator2 = temp2_next;
    }

    if (iterator2) {
        dll1->tail->next = iterator2;
        iterator2->prev = dll1->tail;
        while(iterator2->next) {
            iterator2 = iterator2->next;
        }
        dll1->tail = iterator2;
    }

    dll2->head = NULL;
    dll2->tail = NULL;

    return 0;
}



int dll_concat_begin(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2){
    if(dll1 == NULL || dll2 == NULL) return 1;

    if(dll_is_empty(dll2))
        return 0;
    else if(dll_is_empty(dll1)){
        dll1->head = dll2->head;
        dll1->tail = dll2->tail;
        dll2->head = NULL;
        dll2->tail = NULL;
        return 0;
    }
    dll1->head->prev = dll2->tail;
    dll2->tail->next =dll1->head;
    dll1->head = dll2->head;
    dll2->head = NULL;
    dll2->tail = NULL;


    return 0;
}

int dll_concat_end(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2){
    if(dll1 == NULL || dll2 == NULL) return 1;

    if(dll_is_empty(dll2))
        return 0;
    else if(dll_is_empty(dll1)){
        dll1->head = dll2->head;
        dll1->tail = dll2->tail;
        dll2->head = NULL;
        dll2->tail = NULL;

        return 0;
    }
    dll1->tail->next = dll2->head;
    dll2->head->prev =dll1->tail;
    dll1->tail = dll2->tail;
    dll2->head = NULL;
    dll2->tail = NULL;

    return 0;
}
