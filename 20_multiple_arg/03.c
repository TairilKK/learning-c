#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_HEIGHT 4
#define INPUT_CAPACITY 1001
char * concatenate(int n, ...);
char *my_strcat(char **dest, const char * src);

int main() {
    /* Alokacja */
    char ** input = (char **)calloc(INPUT_HEIGHT, sizeof (char *));
    if(!input){
        printf("Failed to allocate memory");
        return 8;
    }
    for(int i = 0; i < INPUT_HEIGHT; ++i){
        *(input + i) = (char *)calloc(INPUT_CAPACITY, sizeof(char));
        if(!(*(input + i))) {
            for (int j = i - 1; j >= 0; --j)
                free(*(input + j));
            free(input);
            printf("Failed to allocate memory");
            return 8;
        }
    }
    /* Wczytywanie liczby tekstow */
    int n;
    printf("Podaj liczbe tekstow do wprowadzenia: ");
    if(scanf(" %d", &n) != 1){
        printf("Incorrect input");
        for (int i = 0; i < INPUT_HEIGHT; ++i)
            free(*(input + i));
        free(input);
        return 1;
    }
    while(getchar()!='\n');
    if(n < 2 || n > 4){
        printf("Incorrect input data");
        for (int i = 0; i < INPUT_HEIGHT; ++i)
            free(*(input + i));
        free(input);
        return 2;
    }



    /* Pobieranie tekstów */
    char c;
    int j;
    printf("Podaj teksty: ");
    for(int i = 0; i < n; ++i){
        j = 0;
        while((c = getchar()) != '\n' && j < INPUT_CAPACITY - 1) {
            *(*(input + i) + j) = c;
            *(*(input + i) + j + 1) = '\0';
            ++j;
        }
        if(c != '\n')
            while(getchar()!='\n');
    }
    char * result = NULL;
    if(n>2){
        result = concatenate(4, *(input + 0), *(input + 1), *(input + 2), *(input + 3));
    }
    else {
        printf("Incorrect input data");
        free(text);
        free(func);
        free(array_int);
        return 2;
    }
    if(!result){
        for (int i = 0; i < INPUT_HEIGHT; ++i)
            free(*(input + i));
        free(input);
        printf("Failed to allocate memory");
        return 8;
    }
    printf("%s", result);

    for (int i = 0; i < INPUT_HEIGHT; ++i)
        free(*(input + i));
    free(input);
    free(result);

    return 0;
}

char * concatenate(int n, ...){
    if(n < 1)
        return NULL;

    va_list argv;
    va_start(argv, n);
    char * arg = NULL;
    char * temp = NULL;
    char * result = NULL;
    for(int i = 0; i < n; ++ i) {
        arg = va_arg(argv, char *);
        temp = my_strcat(&result, arg);
        if(!temp) {
            free(result);
            va_end(argv);
            return NULL;
        }
        if( i != n - 1) {
            temp = my_strcat(&result, " ");
            if (!temp) {
                free(result);
                va_end(argv);
                return NULL;
            }
        }
    }
    va_end(argv);
    return result;
}

char *my_strcat(char **dest, const char * src){
    if(!dest || !src) return NULL;

    int src_size = (int) strlen(src);
    int dest_size = 0;
    if((*dest))
        dest_size = (int) strlen(*dest);

    char * temp;
    temp = realloc(*dest, (src_size + dest_size + 1) * sizeof(char));

    if(!temp) return NULL;
    strcpy(temp + dest_size, src);
    *dest = temp;
    return *dest;
}
