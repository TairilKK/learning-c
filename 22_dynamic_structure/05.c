#include <stdio.h>

#include "05_linked_list.h"

int main() {
    struct linked_list_t * list = ll_create();
    int op = 1, input, error, res;

    if(list == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    while(op != 0) {
        printf("Co chcesz zrobic? ");
        if (scanf("%d", &op) != 1) {
            ll_destroy(list);
            printf("Incorrect input");
            return 1;
        }

        if(op == 1){
            printf("Podaj liczbe: ");
            if (scanf("%d", &input) != 1) {
                ll_destroy(list);
                printf("Incorrect input");
                return 1;
            }
            res = ll_push_back(list, input);
            if(res == 2){
                printf("Failed to allocate memory");
                ll_destroy(list);
                return 8;
            }
        }
        else if(op == 2){
            if(ll_is_empty(list))
                printf("List is empty\n");
            else{
                printf("%d\n", ll_pop_back(list, &error));
            }
        }
        else if(op == 3){
            printf("Podaj liczbe: ");
            if (scanf("%d", &input) != 1) {
                ll_destroy(list);
                printf("Incorrect input");
                return 1;
            }
            res = ll_push_front(list, input);
            if(res == 2){
                printf("Failed to allocate memory");
                ll_destroy(list);
                return 8;
            }
        }
        else if(op == 4){
            if(ll_is_empty(list))
                printf("List is empty\n");
            else{
                printf("%d\n", ll_pop_front(list, &error));
            }
        }
        else if(op == 5){
            printf("Podaj liczbe: ");
            if (scanf("%d", &input) != 1) {
                ll_destroy(list);
                printf("Incorrect input");
                return 1;
            }
            printf("Podaj indeks: ");
            if (scanf("%d", &error) != 1) {
                ll_destroy(list);
                printf("Incorrect input");
                return 1;
            }
            res = ll_insert(list, error, input);
            if(res == 1){
                printf("Index out of range\n");
            }
            else if( res == 2){
                printf("Failed to allocate memory");
                ll_destroy(list);
                return 8;
            }
        }
        else if(op == 6){
            if(ll_is_empty(list)==1)
                printf("List is empty\n");
            else {
                printf("Podaj indeks: ");
                if (scanf("%d", &input) != 1) {
                    ll_destroy(list);
                    printf("Incorrect input");
                    return 1;
                }
                res = ll_remove(list, input, &error);
                if (error == 1) {
                    printf("Index out of range\n");
                } else printf("%d\n", res);
            }
        }
        else if(op == 7){
            ll_is_empty(list) == 1 ? printf("List is empty\n") : printf("%d\n", ll_back(list, &error));
        }
        else if(op == 8){
            ll_is_empty(list) == 1 ? printf("List is empty\n") : printf("%d\n", ll_front(list, &error));
        }
        else if(op == 9){
            printf("%d\n", ll_is_empty(list));
        }
        else if(op == 10){
            printf("%d\n", ll_size(list));
        }
        else if(op == 11){
            ll_clear(list);
        }
        else if(op == 12) {
            if (ll_is_empty(list) == 1)
                printf("List is empty\n");
            else {
                printf("Podaj indeks: ");
                if (scanf("%d", &input) != 1) {
                    ll_destroy(list);
                    printf("Incorrect input");
                    return 1;
                }
                res = ll_at(list, input, &error);
                if (error == 1)
                    printf("Index out of range");
                else printf("%d", res);
                printf("\n");

            }
        }
        else if(op == 13){
            if(ll_is_empty(list))
                printf("List is empty");
            else
                ll_display(list);
            printf("\n");
        }
        else
            printf("Incorrect input data\n");
    }
    ll_destroy(list);
    return 0;
}
