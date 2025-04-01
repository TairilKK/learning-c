#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int is_letter(char c){
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0;
}

int* count_words(const char *filename, int *err_code, int N, ...) {
    if(!filename || N < 1){if(err_code)*err_code = 1; return NULL;}

    FILE * f = fopen(filename, "r");
    if(!f){if(err_code)*err_code = 2; return NULL;}
    char c = fgetc(f);
    if(c == EOF){if(err_code)*err_code = 2; return NULL;}

    int * res = calloc(N, sizeof(int));
    if(!res){if(err_code)*err_code = 3; fclose(f); return NULL;}

    va_list v;
    va_start(v, N);
    char * arg = NULL;
    int size;
    int check;
    for(int i = 0; i < N; ++i){
        fseek(f, 0, SEEK_SET);
        arg = va_arg(v, char *);
        size = strlen(arg);
        check = 0;
        while((c = fgetc(f))){
            if(check == size && is_letter(c) == 0) {
                (*(res + i))++;
                check = 0;
            }
            if(c == *(arg + check))
                check++;
            else {
                while(is_letter(c)==1)
                    c = fgetc(f);
                check = 0;
            }

            if(c == EOF)
                break;
        }
    }

    if(err_code)*err_code = 0;
    fclose(f);
    va_end(v);
    return res;
}

int main(int argc, char** argv) {
    if(argc < 3) {
        printf("Not enough arguments");
        return 9;
    }
    int err = 0;
    int * res = count_words(*(argv + 1), &err, argc - 2, *(argv + 2), *(argv + 3), *(argv + 4), *(argv + 5), *(argv + 6), *(argv + 7), *(argv + 8), *(argv + 9), *(argv + 10), *(argv + 11), *(argv + 12), *(argv + 13), *(argv + 14), *(argv + 15), *(argv + 16), *(argv + 17), *(argv + 18), *(argv + 19), *(argv + 20));
    if(err == 2) {
        printf("Couldn't open file");
        return 4;
    }
    else if (err == 3){
        printf("Failed to allocate memory");
        return 8;
    }
    for(int i = 0; i < argc - 2; ++i)
        printf("%d\n",*(res + i));
    free(res);
    return 0;
}
