//
// Created by jdobr on 23.08.2023.
//

#ifndef INC_12_STATISTICS_H
#define INC_12_STATISTICS_H

#include "statistics.h"
#include "format_type.h"

struct statistic_t
{
    int min;
    int max;
    float avg;
    float standard_deviation;
    int range;
};

int load(const char *filename, int ***ptr, enum save_format_t format);
void destroy(int ***ptr);
void display(int **ptr);

int statistics_row(int **ptr, struct statistic_t **stats);

int find_min_row(const int** arr, int row_number);
int find_max_row(const int** arr, int row_number);
float find_avg_row(const int** arr, int row_number);
float find_standard_deviation_row(const int** arr, int row_number);

#endif //INC_12_STATISTICS_H
