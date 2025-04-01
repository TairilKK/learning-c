//
// Created by jdobr on 14.08.2023.
//
#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

struct linked_list_t* ll_create(){
    struct  linked_list_t * list = (struct linked_list_t *) calloc(1, sizeof(struct linked_list_t));
    if(list != NULL){
        list->head = NULL;
        list->tail = NULL;
    }
    return list;
}

void ll_destroy(struct linked_list_t * ll){
    if (ll == NULL)
        return;
    ll_clear(ll);
    free(ll);
}

int ll_push_back(struct linked_list_t* ll, int value){
    if(ll == NULL)
        return 1;

    struct node_t * newNode = (struct node_t *)calloc(1, sizeof (struct node_t));
    if(newNode == NULL)
        return 2;
    newNode->data = value;
    newNode->next = NULL;

    /* Empty list */
    if(ll->head == NULL) {
        ll->head = newNode;
        ll->tail = newNode;
        return 0;
    }

    ll->tail->next = newNode;
    ll->tail = newNode;
    return 0;
}

int ll_push_front(struct linked_list_t* ll, int value){
    if(ll == NULL)
        return 1;

    struct node_t * newNode = (struct node_t *)calloc(1, sizeof (struct node_t));
    if(newNode == NULL)
        return 2;

    newNode->data = value;
    newNode->next = NULL;

    /* Empty list */
    if(ll->head == NULL) {
        ll->head = newNode;
        ll->tail = newNode;
        return 0;
    }
    newNode->next = ll->head;
    ll->head = newNode;
    return 0;
}

int ll_pop_front(struct linked_list_t* ll, int *err_code){
    if(ll == NULL || ll->head == NULL || ll->tail == NULL){
        ERROR(1);
        return 0;
    }
    int res;
    if(ll->head == ll->tail){
        res = ll->head->data;
        free(ll->head);
        ll->head = NULL;
        ll->tail = NULL;
        ERROR(0);
        return res;
    }
    struct node_t * temp = ll->head;
    ll->head = temp->next;

    res = temp->data;
    free(temp);

    ERROR(0);
    return res;
}

int ll_pop_back(struct linked_list_t* ll, int *err_code){
    if(ll == NULL || ll->head == NULL || ll->tail == NULL){
        ERROR(1);
        return 0;
    }
    int res;
    if(ll->head == ll->tail){
        res = ll->head->data;
        free(ll->head);
        ll->head = NULL;
        ll->tail = NULL;

        ERROR(0);
        return res;
    }

    struct node_t * temp = ll->tail;

    struct node_t * iterator = ll->head;
    while(iterator->next != temp)
        iterator = iterator->next;

    iterator->next = NULL;
    ll->tail = iterator;

    res = temp->data;
    free(temp);

    ERROR(0);
    return res;
}

int ll_front(const struct linked_list_t* ll, int *err_code){
    if(ll == NULL || ll->head == NULL || ll->tail == NULL){
        ERROR(1);
        return 0;
    }
    ERROR(0);
    return ll->head->data;
}
int ll_back(const struct linked_list_t* ll, int *err_code){
    if(ll == NULL || ll->head == NULL || ll->tail == NULL){
        ERROR(1);
        return 0;
    }
    ERROR(0);
    return ll->tail->data;
}

struct node_t* ll_begin(struct linked_list_t* ll){
    if(ll == NULL)
        return NULL;
    return ll->head;
}
struct node_t* ll_end(struct linked_list_t* ll){
    if(ll == NULL)
        return NULL;
    return ll->tail;
}

int ll_size(const struct linked_list_t* ll){
    if(ll == NULL)
        return -1;

    int res = 0;
    struct node_t * temp = ll->head;
    while(temp != NULL){
        ++res;
        temp = temp->next;
    }
    return res;
}
int ll_is_empty(const struct linked_list_t* ll){
    if(ll == NULL)
        return -1;
    return ll->head == NULL ? 1 : 0;
}

int ll_at(const struct linked_list_t* ll, unsigned int index, int *err_code){
    if(ll == NULL || index >= (unsigned int) ll_size(ll) || ll_is_empty(ll) == 1){
        ERROR(1);
        return 0;
    }
    struct node_t * temp = ll->head;
    for(unsigned int i = 0; i < index; temp = temp->next, ++i);

    ERROR(0);
    return temp->data;
}

int ll_insert(struct linked_list_t* ll, unsigned int index, int value){
    if(ll == NULL || index > (unsigned int) ll_size(ll) || (ll_is_empty(ll) == 1 && index != 0))
        return 1;

    if(index == 0)
        return ll_push_front(ll, value);
    else if(index == (unsigned int) ll_size(ll))
        return ll_push_back(ll, value);

    struct node_t * temp = ll->head;
    for(unsigned int i = 0; i < index - 1; temp = temp->next, ++i);

    struct node_t * newNode = (struct node_t *) calloc(1, sizeof (struct node_t));
    if(newNode == NULL)
        return 2;

    newNode->next = temp->next;
    newNode->data = value;
    temp->next = newNode;

    return 0;
}

int ll_remove(struct linked_list_t* ll, unsigned int index, int *err_code){
    if(ll == NULL || index > (unsigned int) ll_size(ll) || ll_is_empty(ll) == 1) {
        ERROR(1);
        return 0;
    }
    if(index == 0)
        return ll_pop_front(ll, err_code);
    else if(index == (unsigned int) ll_size(ll))
        return ll_pop_back(ll, err_code);

    struct node_t * temp = ll->head;
    for(unsigned int i = 0; i < index; temp = temp->next, ++i);

    struct node_t * before_temp = ll->head;
    while(before_temp->next != temp)
        before_temp = before_temp->next;

    int res = temp->data;
    before_temp->next = temp->next;

    free(temp);

    ERROR(0);
    return res;
}

void ll_clear(struct linked_list_t* ll){
    if (ll == NULL)
        return;
    struct node_t * temp = ll->head;
    while(temp != NULL) {
        ll->head = temp->next;
        free(temp);
        temp = ll->head;
    }
    ll->head = NULL;
    ll->tail = NULL;
}

void ll_display(const struct linked_list_t* ll){
    if(ll == NULL)
        return;

    struct node_t * temp = ll->head;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}