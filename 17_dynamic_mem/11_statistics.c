//
// Created by jdobr on 23.08.2023.
//
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "statistics.h"
#include "format_type.h"

int load(const char *filename, int ***ptr, enum save_format_t format){
    if(!filename || !ptr || (format != fmt_text && format != fmt_binary)) return 1;

    FILE *f;
    if(format == fmt_text)
        f = fopen(filename, "r");
    else
        f = fopen(filename, "rb");

    if(!f) return 2;

    int input, count = 0;

    fseek(f, 0, SEEK_SET);
    if(feof(f)){
        fclose(f);
        return 3;
    }

    char temp;
     /* TEXT */
    if(format == fmt_text) {
        while (fgetc(f) != EOF) {
            fseek(f, -1, SEEK_CUR);
            if (fscanf(f, " %d%c", &input, &temp) != 2) {
                fclose(f);
                return 3;
            }
            if (input == -1)
                count++;
        }

        if (count == 0) {
            fclose(f);
            return 3;
        }

        (*ptr) = (int **) calloc(count + 1, sizeof(int *));
        if (!(*ptr)) {
            fclose(f);
            return 4;
        }
        *((*ptr) + count) = NULL;

        int i = 0;
        int row_count = 0;
        fseek(f, 0, SEEK_SET);

        while (fgetc(f) != EOF) {
            fseek(f, -1, SEEK_CUR);
            if (fscanf(f, " %d%c", &input, &temp) != 2) {
                fclose(f);
                return 3;
            }
            if (input == -1) {
                *((*ptr) + i) = calloc(row_count + 1, sizeof(int));
                if (!*((*ptr) + i)) {
                    destroy(ptr);
                    fclose(f);
                    return 4;
                }
                row_count = 0;
                i++;
            } else row_count++;
        }

        fseek(f, 0, SEEK_SET);
        int j = i = 0;
        fseek(f, 0, SEEK_SET);
        while (fgetc(f) != EOF && *((*ptr) + i) != NULL) {
            fseek(f, -1, SEEK_CUR);
            if (fscanf(f, " %d%c", &input, &temp) != 2) {
                destroy(ptr);
                fclose(f);
                return 3;
            }
            *(*((*ptr) + i) + j) = input;
            if (input == -1) {
                i++;
                j = 0;
            } else {
                j++;
            }
        }
    }

    /* BIN */
    else {
        while (fread(&input, sizeof(int), 1, f) == 1) {
            if (input == -1)
                count++;
        }

        if (count == 0) {
            fclose(f);
            return 3;
        }

        (*ptr) = (int **)calloc(count + 1, sizeof(int *));
        if (!(*ptr)) {
            fclose(f);
            return 4;
        }
        *((*ptr) + count) = NULL;

        int i = 0;
        int row_count = 0;
        fseek(f, 0, SEEK_SET);

        while (fread(&input, sizeof(int), 1, f) == 1) {
            if (input == -1) {
                *((*ptr) + i) = calloc(row_count + 1, sizeof(int));
                if (!*((*ptr) + i)) {
                    destroy(ptr);
                    fclose(f);
                    return 4;
                }
                row_count = 0;
                i++;
            } else row_count++;
        }

        fseek(f, 0, SEEK_SET);
        int j = i = 0;
        while (fread(&input, sizeof(int), 1, f) == 1 && *((*ptr) + i) != NULL) {
            *(*((*ptr) + i) + j) = input;
            if (input == -1) {
                i++;
                j = 0;
            } else {
                j++;
            }
        }
    }

    fclose(f);
    return 0;
}

void destroy(int ***ptr){
    if(!ptr || !(*ptr)) return;
    for(int i = 0; *((*ptr) + i); free(*((*ptr) + i)), ++i);
    free(*ptr);
    *ptr = NULL;
}
void display(int **ptr){
    if(ptr == NULL) return;
    for(int i = 0; *(ptr + i); putchar('\n'), ++i)
        for(int j = 0; *(*(ptr + i) + j) != -1; printf("%d ",*(*(ptr + i) + j)), j++);
}


int statistics_row(int **ptr, struct statistic_t **stats){
    if(ptr==NULL||stats==NULL)
        return -1;

    if(*ptr==NULL)
        return -3;

    int c=0;
    int t=0;
    for(int i=0;*(ptr+i); ++i) {
        t++;
        if(*(*(ptr + i))==-1)
            c++;
    }
    if(t==c)
        return -3;

    *stats = calloc(t, sizeof(struct statistic_t));
    if(*stats==NULL)
        return -2;



    for(int i = 0; i < t; ++i) {
        (*stats + i)->avg = find_avg_row((const int **) ptr, i);
        (*stats + i)->min = find_min_row((const int **) ptr, i);
        (*stats + i)->max = find_max_row((const int **) ptr, i);
        if((*stats + i)->min == -1) (*stats + i)->range = -1;
        else (*stats + i)->range = (*stats + i)->max - (*stats + i)->min;
        (*stats + i)->standard_deviation = find_standard_deviation_row((const int **) ptr, i);
    }

    return t;
}

/* pomocnicze */
int find_min_row(const int** arr, int i) {
    int min = *(*(arr+ i));
    if(min == -1) return -1;

    for (int j = 0; *(*(arr + i) + j) != -1; ++j)
        if (*(*(arr + i) + j) < min)
            min = *(*(arr + i) + j);


    return min;
}

int find_max_row(const int** arr, int i) {
    int max = *(*(arr + i));
    if(max == -1) return -1;

    for (int j = 0; *(*(arr + i) + j) != -1; ++j)
        if (*(*(arr + i) + j) > max)
            max = *(*(arr + i) + j);


    return max;
}
float find_avg_row(const int** arr, int i) {
    int temp=0;
    int size=0;


    if(*(*(arr+i)) == -1) return -1;

    for (int j = 0; *(*(arr + i) + j) != -1; ++j) {
        temp += *(*(arr + i) + j);
        ++size;
    }

    return (float)temp/(float)size;
}

float find_standard_deviation_row(const int** arr, int i){
    float avg = find_avg_row(arr, i);
    float ssd=0;
    float temp=0;
    int l=0;

    if(*(*(arr+i)) == -1) return -1;

    for (int j = 0; *(*(arr + i) + j) != -1; ++j) {
            temp = (float) *(*(arr + i) + j) - avg;
            ssd += temp * temp;
            ++l;
    }

    float sd=sqrt(ssd/l);

    return sd;
}