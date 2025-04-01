#include <stdio.h>
#include <stdlib.h>

int main() {
    int capacity = 50;
    int i = 0;

    char * input = NULL;
    char * temp = realloc(input, capacity * sizeof(char));
    if(temp == NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    input = temp;
    *input = '\0';

    printf("Podaj tekst: ");
    char c;
    while((c = getchar()) != '\n'){
        if(i == capacity - 1){
            capacity += 50;
            temp = realloc(input, capacity * sizeof(char));
            if(temp == NULL){
                printf("%s", input);
                free(input);
                return 0;
            }
            input = temp;
        }
        *(input + i) = c;
        i++;
        *(input + i) = '\0';
    }
    printf("%s", input);
    free(input);
    return 0;
}
