#include <stdio.h>

#include "06_doubly_linked_list.h"

int main() {
    struct doubly_linked_list_t * pDoublyLinkedList = dll_create();
    int op = 1, input, error, res;

    if(pDoublyLinkedList == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    while(op != 0) {
        printf("Co chcesz zrobic? ");
        if (scanf("%d", &op) != 1) {
            dll_destroy(pDoublyLinkedList);
            printf("Incorrect input");
            return 1;
        }

        if(op == 1){
            printf("Podaj liczbe: ");
            if (scanf("%d", &input) != 1) {
                dll_destroy(pDoublyLinkedList);
                printf("Incorrect input");
                return 1;
            }
            res = dll_push_back(pDoublyLinkedList, input);
            if(res == 2){
                printf("Failed to allocate memory");
                dll_destroy(pDoublyLinkedList);
                return 8;
            }
        }
        else if(op == 2){
            if(dll_is_empty(pDoublyLinkedList))
                printf("List is empty\n");
            else{
                printf("%d\n", dll_pop_back(pDoublyLinkedList, &error));
            }
        }
        else if(op == 3){
            printf("Podaj liczbe: ");
            if (scanf("%d", &input) != 1) {
                dll_destroy(pDoublyLinkedList);
                printf("Incorrect input");
                return 1;
            }
            res = dll_push_front(pDoublyLinkedList, input);
            if(res == 2){
                printf("Failed to allocate memory");
                dll_destroy(pDoublyLinkedList);
                return 8;
            }
        }
        else if(op == 4){
            if(dll_is_empty(pDoublyLinkedList))
                printf("List is empty\n");
            else{
                printf("%d\n", dll_pop_front(pDoublyLinkedList, &error));
            }
        }
        else if(op == 5){
            printf("Podaj liczbe: ");
            if (scanf("%d", &input) != 1) {
                dll_destroy(pDoublyLinkedList);
                printf("Incorrect input");
                return 1;
            }
            printf("Podaj indeks: ");
            if (scanf("%d", &error) != 1) {
                dll_destroy(pDoublyLinkedList);
                printf("Incorrect input");
                return 1;
            }
            res = dll_insert(pDoublyLinkedList, error, input);
            if(res == 1){
                printf("Index out of range\n");
            }
            else if( res == 2){
                printf("Failed to allocate memory");
                dll_destroy(pDoublyLinkedList);
                return 8;
            }
        }
        else if(op == 6){
            if(dll_is_empty(pDoublyLinkedList) == 1)
                printf("List is empty\n");
            else {
                printf("Podaj indeks: ");
                if (scanf("%d", &input) != 1) {
                    dll_destroy(pDoublyLinkedList);
                    printf("Incorrect input");
                    return 1;
                }
                res = dll_remove(pDoublyLinkedList, input, &error);
                if (error == 1) {
                    printf("Index out of range\n");
                } else printf("%d\n", res);
            }
        }
        else if(op == 7){
            dll_is_empty(pDoublyLinkedList) == 1 ? printf("List is empty\n") : printf("%d\n", dll_back(pDoublyLinkedList, &error));
        }
        else if(op == 8){
            dll_is_empty(pDoublyLinkedList) == 1 ? printf("List is empty\n") : printf("%d\n", dll_front(pDoublyLinkedList, &error));
        }
        else if(op == 9){
            printf("%d\n", dll_is_empty(pDoublyLinkedList));
        }
        else if(op == 10){
            printf("%d\n", dll_size(pDoublyLinkedList));
        }
        else if(op == 11){
            dll_clear(pDoublyLinkedList);
        }
        else if(op == 12) {
            if (dll_is_empty(pDoublyLinkedList) == 1)
                printf("List is empty\n");
            else {
                printf("Podaj indeks: ");
                if (scanf("%d", &input) != 1) {
                    dll_destroy(pDoublyLinkedList);
                    printf("Incorrect input");
                    return 1;
                }
                res = dll_at(pDoublyLinkedList, input, &error);
                if (error == 1)
                    printf("Index out of range");
                else printf("%d", res);
                printf("\n");

            }
        }
        else if(op == 13){
            if(dll_is_empty(pDoublyLinkedList))
                printf("List is empty");
            else
                dll_display(pDoublyLinkedList);
            printf("\n");
        }
        else if(op == 14){
            if(dll_is_empty(pDoublyLinkedList))
                printf("List is empty");
            else
                dll_display_reverse(pDoublyLinkedList);
            printf("\n");
        }
        else
            printf("Incorrect input data\n");
    }
    dll_destroy(pDoublyLinkedList);
    return 0;
}
