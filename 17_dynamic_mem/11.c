#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "11_statistics.h"
#include "11_format_type.h"

int main() {
    display(NULL);
    char * filename = calloc(40, sizeof(char));
    if(!filename){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj nazwe pliku: ");
    int i = 0;
    char c = 0;
    while ((c = getchar()) != '\n' && i < 39) {
        *(filename + i) = c;
        ++i;
    }
    *(filename + i) = '\0';
    if (c != '\n')
        while (getchar() != '\n');


    enum save_format_t format;
    if(!strcmp(filename + strlen(filename) - 4, ".txt")) format = fmt_text;
    else if(!strcmp(filename + strlen(filename) - 4, ".bin")) format = fmt_binary;
    else{
        printf("Unsupported file format");
        free(filename);
        return 7;
    }
    int ** ptr = NULL;
    int size = load(filename, &ptr , format);

    if(size == 2){
        printf("Couldn't open file");
        free(filename);
        return 4;
    }
    else if(size == 3){
        printf("File corrupted");
        free(filename);
        return 6;
    }
    else if(size == 4){
        printf("Failed to allocate memory");
        free(filename);
        return 8;
    }

    struct statistic_t * pStat = NULL;

    size = statistics_row(ptr, &pStat);
    if(size == -2){
        printf("Failed to allocate memory");
        destroy(&ptr);
        free(filename);
        return 4;
    }

    for(int i = 0; i < size; ++i)
        printf("%d %d %d %.2f %.2f\n", (pStat + i)->min, (pStat + i)->max, (pStat + i)->range, (pStat + i)->avg, (pStat + i)->standard_deviation);

    destroy(&ptr);
    free(pStat);
    free(filename);

    return 0;
}
