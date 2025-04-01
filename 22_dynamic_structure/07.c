#include <stdio.h>

#include "07_doubly_linked_list.h"

int main() {
    struct doubly_linked_list_t * dll1 = dll_create();
    if(dll1 == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }

    struct doubly_linked_list_t * dll2 = dll_create();
    if(dll2 == NULL)
    {
        printf("Failed to allocate memory");
        dll_destroy(dll1);
        return 8;
    }

    int input = 0;
    printf("Enter first list (-1 when done):");
    do
    {
        if(scanf("%d", &input) != 1)
        {
            printf("Incorrect input");
            dll_destroy(dll1);
            dll_destroy(dll2);
            return 1;
        }
        if(input == -1)
            break;
        if(dll_push_back(dll1, input) != 0)
        {
            printf("Failed to allocate memory");
            dll_destroy(dll1);
            dll_destroy(dll2);
            return 8;
        }
    }while(input != -1);

    input = 0;
    printf("Enter second list (-1 when done):");
    do
    {
        if(scanf("%d", &input) != 1)
        {
            printf("Incorrect input");
            dll_destroy(dll1);
            dll_destroy(dll2);
            return 1;
        }
        if(input == -1)
            break;
        if(dll_push_back(dll2, input) != 0)
        {
            printf("Failed to allocate memory");
            dll_destroy(dll1);
            dll_destroy(dll2);
            return 8;
        }
    }while(input != -1);

    if(dll_is_empty(dll1) && dll_is_empty(dll2))
    {
        printf("Not enough data available");
        dll_destroy(dll1);
        dll_destroy(dll2);
        return 3;
    }
    printf("Choose method (0, 1 or 2):");
    if(scanf("%d", &input) != 1)
    {
        printf("Incorrect input");
        dll_destroy(dll1);
        dll_destroy(dll2);
        return 1;
    }
    if(input < 0 || input > 2)
    {
        printf("Incorrect input data");
        dll_destroy(dll1);
        dll_destroy(dll2);
        return 2;
    }
    if(input == 0)
        dll_concat_zip(dll1, dll2);
    else if(input == 1)
        dll_concat_begin(dll1, dll2);
    else if(input == 2)
        dll_concat_end(dll1, dll2);

    dll_display(dll1);
    putchar('\n');
    dll_display_reverse(dll1);

    dll_destroy(dll1);
    dll_destroy(dll2);
    return 0;
}
