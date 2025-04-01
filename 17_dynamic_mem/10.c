#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "10_format_type.h"

int find_min(const int** arr);
int find_max(const int** arr);
float find_avg(const int** arr);
float find_standard_deviation(const int** arr);

struct statistic_t
{
    int min;
    int max;
    float avg;
    float standard_deviation;
    int range;
};

int statistics(int **ptr, struct statistic_t **stats);
void display(int **ptr);
int save(const char *filename, int **ptr, enum save_format_t format);

int main() {
    int A[] = {10, 20, 30, 40, 50, 60, 70, -1};
    int B[] = {100, 200, 300, 400, 500, 600, 700, 800, -1};
    int C[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, -1};
    int* D[] = {A, B, C, NULL};

    display(D);

    char *buffer = calloc(40, sizeof(char));
    if (buffer == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj nazwe pliku: ");
    if (scanf("%39s", buffer) != 1) {
        printf("Incorrect input");
        free(buffer);
        return 1;
    }

    char *nbuffer = realloc(buffer, 50);
    if (nbuffer == NULL) {
        free(buffer);
        printf("Failed to allocate memory");
        return 8;
    }
    buffer = nbuffer;

    struct statistic_t *stats;
    int er = statistics(D, &stats);

    if (er == 2) {
        printf("Failed to allocate memory");
        free(buffer);
        return 8;
    }


    er = save(strcat(buffer, ".txt"), D, fmt_text);
    if (er != 0)
        printf("Couldn't create file\n");
    else
        printf("File saved\n");
    int len = (int) strlen(buffer);
    strcpy(buffer + len - 4, "");
    er = save(strcat(buffer, ".bin"), D, fmt_binary);
    if (er != 0)
        printf("Couldn't create file\n");
    else
        printf("File saved\n");

    if(stats!=NULL) {
        printf("%d\n%d\n%d\n%f\n%f", stats->min, stats->max, stats->range, stats->avg, stats->standard_deviation);
        free(stats);
    }
    free(buffer);

    return 0;
}


int statistics(int **ptr, struct statistic_t **stats){
    if(ptr==NULL||stats==NULL)
        return 1;

    if(*ptr==NULL)
        return 3;

    int c=0;
    int t=0;
    for(int i=0;*(ptr+i)!=NULL;++i) {
        t++;
        if(*(*(ptr + i))==-1)
            c++;
    }
    if(t==c)
        return 3;

    *stats = calloc(1, sizeof(struct statistic_t));
    if(*stats==NULL)
        return 2;

    (*stats)->avg = find_avg((const int**)ptr);
    (*stats)->min = find_min((const int**)ptr);
    (*stats)->max = find_max((const int**)ptr);
    (*stats)->range = (*stats)->max-(*stats)->min;
    (*stats)->standard_deviation = find_standard_deviation((const int**)ptr);


    return 0;
}

void display(int **ptr){
    if(ptr==NULL)
        return;
    if(*ptr==NULL)
        return;

    for(int i=0;*(ptr+i)!=NULL;++i) {
        for (int j = 0; *(*(ptr + i) + j) != -1; ++j)
            printf("%d ",*(*(ptr + i) + j));
        printf("\n");
    }
}

int save(const char *filename, int **ptr, enum save_format_t format){
    if(filename==NULL||ptr==NULL)
        return 1;
    if(*ptr==NULL)
        return 1;

    FILE *pFile;

    if(format==fmt_text) {
        pFile = fopen(filename, "w");
        if(pFile==NULL)
            return 2;
        for(int i=0;*(ptr+i)!=NULL;++i) {
            for (int j = 0; *(*(ptr + i) + j) != -1; ++j)
                fprintf(pFile, "%d ", *(*(ptr + i) + j));
            fprintf(pFile,"-1\n");
        }
    }
    else if(format==fmt_binary) {
        pFile = fopen(filename, "wb");
        if(pFile==NULL)
            return 2;
        int v=-1;
        for(int i=0;*(ptr+i)!=NULL;++i) {
            for (int j = 0; *(*(ptr + i) + j) != -1; ++j) {
                fwrite((*(ptr + i) + j), sizeof(int), 1, pFile);
            }
            fwrite(&v,sizeof(int),1,pFile);
        }
    }
    else
        return 1;

    fclose(pFile);

    return 0;
}


/* pomocnicze */
int find_min(const int** arr) {
    int min = **arr;
    for (int i = 0; *(arr + i) != NULL; ++i) {
        for (int j = 0; *(*(arr + i) + j) != -1; ++j)
            if (*(*(arr + i) + j) < min)
                min = *(*(arr + i) + j);
    }

    return min;
}

int find_max(const int** arr) {
    int max = **arr;
    for(int i=0;*(arr+i)!=NULL;++i) {
        for (int j = 0; *(*(arr + i) + j) != -1; ++j)
            if (*(*(arr + i) + j) > max)
                max = *(*(arr + i) + j);
    }

    return max;
}
float find_avg(const int** arr) {
    int temp=0;
    int size=0;
    for(int i=0;*(arr+i)!=NULL;++i) {
        for (int j = 0; *(*(arr + i) + j) != -1; ++j) {
            temp += *(*(arr + i) + j);
            ++size;
        }
    }


    return (float)temp/(float)size;
}

float find_standard_deviation(const int** arr){
    float avg = find_avg(arr);

    float ssd=0;
    float temp;
    int l=0;

    for(int i=0;*(arr+i)!=NULL;++i) {
        for (int j = 0; *(*(arr + i) + j) != -1; ++j) {
            temp = (float) *(*(arr + i) + j) - avg;
            ssd += temp * temp;
            ++l;
        }
    }
    float sd=sqrtf(ssd/(float)l);

    return sd;
}
