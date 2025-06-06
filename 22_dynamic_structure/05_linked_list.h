//
// Created by jdobr on 14.08.2023.
//

#ifndef INC_07_LINKED_LIST_H
#define INC_07_LINKED_LIST_H

#define ERROR(error_code) \
do{                          \
if(err_code != NULL) *err_code = error_code;}\
while(0)

struct node_t
{
    int data;
    struct node_t *next;
};

struct linked_list_t
{
    struct node_t *head;
    struct node_t *tail;
};

struct linked_list_t* ll_create();
void ll_destroy(struct linked_list_t * ll);


int ll_push_back(struct linked_list_t* ll, int value);
int ll_push_front(struct linked_list_t* ll, int value);
int ll_pop_front(struct linked_list_t* ll, int *err_code);
int ll_pop_back(struct linked_list_t* ll, int *err_code);

int ll_back(const struct linked_list_t* ll, int *err_code);
int ll_front(const struct linked_list_t* ll, int *err_code);

struct node_t* ll_begin(struct linked_list_t* ll);
struct node_t* ll_end(struct linked_list_t* ll);

int ll_size(const struct linked_list_t* ll);
int ll_is_empty(const struct linked_list_t* ll);
int ll_at(const struct linked_list_t* ll, unsigned int index, int *err_code);

int ll_insert(struct linked_list_t* ll, unsigned int index, int value);

int ll_remove(struct linked_list_t* ll, unsigned int index, int *err_code);

void ll_clear(struct linked_list_t* ll);

void ll_display(const struct linked_list_t* ll);



#endif //INC_07_LINKED_LIST_H
