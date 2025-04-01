//
// Created by jdobr on 14.08.2023.
//
#include <stdio.h>
#include <stdlib.h>

#include "06_doubly_linked_list.h"

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

struct node_t* dll_begin(struct doubly_linked_list_t* dll){
    return dll == NULL ? NULL : dll->head;
}
struct node_t* dll_end(struct doubly_linked_list_t* dll){
    return dll == NULL ? NULL : dll->tail;
}


int dll_back(const struct doubly_linked_list_t* dll, int *err_code){
    if(dll == NULL || dll->head == NULL) {
        ERROR(1);
        return 0;
    }
    ERROR(0);
    return dll->tail->data;
}
int dll_front(const struct doubly_linked_list_t* dll, int *err_code){
    if(dll == NULL || dll->head == NULL) {
        ERROR(1);
        return 0;
    }
    ERROR(0);
    return dll->head->data;
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


int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code){
    if(dll == NULL || index >= (unsigned int) dll_size(dll)){
        ERROR(1);
        return 0;
    }
    struct node_t * temp = dll->head;
    for(unsigned int i = 0; i<index; temp=temp->next, ++i);

    ERROR(0);
    return temp->data;
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

int dll_push_front(struct doubly_linked_list_t* dll, int value){
    if(dll == NULL) return 1;

    struct node_t * newNode = (struct node_t *)calloc(1, sizeof (struct node_t));
    if(newNode == NULL) return 2;

    if(dll_is_empty(dll))
        dll->tail = newNode;

    newNode->data = value;
    newNode->next = dll->head;
    newNode->prev = NULL;
    if(dll->head != NULL)
        dll->head->prev = newNode;

    dll->head = newNode;

    return 0;
}

int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code){
    if(dll == NULL || dll_is_empty(dll) == 1){
        ERROR(1);
        return 0;
    }

    struct node_t * temp = dll->head;
    int res = temp->data;

    dll->head = temp->next;
    if(dll->head != NULL)
        dll->head->prev = NULL;
    else
        dll->tail = NULL;
    free(temp);
    ERROR(0);
    return res;
}

int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code){
    if(dll == NULL || dll_is_empty(dll) == 1){
        ERROR(1);
        return 0;
    }

    struct node_t * temp = dll->tail;
    int res = temp->data;

    dll->tail = temp->prev;
    if(dll->tail != NULL)
        dll->tail->next = NULL;
    else
        dll->head = NULL;

    free(temp);
    ERROR(0);
    return res;
}

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value){
    if(dll == NULL || index > (unsigned int) dll_size(dll) || (dll_is_empty(dll) == 1 && index != 0))
        return 1;

    if(index == 0)
        return dll_push_front(dll, value);
    else if(index == (unsigned int) dll_size(dll))
        return dll_push_back(dll, value);

    struct node_t * temp = dll->head;
    for(unsigned int i = 0; i < index - 1; temp = temp->next, ++i);

    struct node_t * newNode = (struct node_t *) calloc(1, sizeof (struct node_t));
    if(newNode == NULL)
        return 2;

    newNode->data = value;
    newNode->next = temp->next;
    newNode->prev = temp;

    temp->next->prev = newNode;
    temp->next = newNode;
    return 0;

}
int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code){
    if(dll == NULL || index > (unsigned int) dll_size(dll) || (dll_is_empty(dll) == 1 && index != 0)) {
        ERROR(1);
        return 1;
    }

    if(index == 0)
        return dll_pop_front(dll, err_code);
    else if(index == (unsigned int) dll_size(dll) - 1)
        return dll_pop_back(dll, err_code);

    struct node_t * temp = dll->head;
    for(unsigned int i = 0; i < index;temp = temp->next, ++i);


    int res = temp->data;
    temp->prev->next = temp->next;
    if(temp->next != NULL)
        temp->next->prev = temp->prev;

    free(temp);

    ERROR(0);
    return res;
}
