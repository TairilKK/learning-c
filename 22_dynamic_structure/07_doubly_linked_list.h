//
// Created by jdobr on 14.08.2023.
//

#ifndef INC_10_DOUBLY_LINKED_LIST_H
#define INC_10_DOUBLY_LINKED_LIST_H

#define ERROR(error_code)                       \
do{                                             \
if(err_code != NULL){*err_code = error_code;}   \
}while(0)

struct doubly_linked_list_t
{
    struct node_t *head;
    struct node_t *tail;
};

struct node_t
{
    int data;
    struct node_t *next;
    struct node_t *prev;
};

struct doubly_linked_list_t* dll_create();

void dll_clear(struct doubly_linked_list_t* dll);
void dll_destroy(struct doubly_linked_list_t* dll);

int dll_push_back(struct doubly_linked_list_t* dll, int value);

int dll_size(const struct doubly_linked_list_t* dll);
int dll_is_empty(const struct doubly_linked_list_t* dll);

void dll_display(const struct doubly_linked_list_t* dll);
void dll_display_reverse(const struct doubly_linked_list_t* dll);

int dll_concat_zip(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2);
int dll_concat_begin(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2);
int dll_concat_end(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2);

#endif //INC_10_DOUBLY_LINKED_LIST_H
