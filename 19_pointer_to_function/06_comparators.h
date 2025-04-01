//
// Created by jdobr on 05.06.2023.
//

#ifndef INC_08_COMPARATORS_H
#define INC_08_COMPARATORS_H



struct point_t
{
    double x;
    double y;
};

int comp_int(const void *a, const void *b);
int comp_double(const void *a, const void *b);
int comp_point(const void *a, const void *b);

int sort(void * array, int array_size, int element_size, int(*func)(const void*, const void*));
//void swap(void** a, void** b);
void swap(void* a, void* b, int element_size);

#endif //INC_08_COMPARATORS_H
