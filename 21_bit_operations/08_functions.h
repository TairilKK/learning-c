#ifndef INC_15_FUNCTIONS_H
#define INC_15_FUNCTIONS_H

#define DEFINE_ARRAY(TYPE) \
struct array_##TYPE##_t { \
    int size; \
    int capacity; \
    TYPE *data; \
};

#define CREATE_ARRAY(TYPE) \
struct array_##TYPE##_t *create_array_##TYPE(int size){ \
    if(size < 1) return NULL;                     \
    struct array_##TYPE##_t * array;                     \
    array = calloc(1, sizeof(struct array_##TYPE##_t));  \
    if(array == NULL) return NULL;                       \
    array->data = calloc(size, sizeof(TYPE));            \
    if(array->data == NULL){free(array); return NULL;}   \
    array->capacity = size;\
    array->size = 0;       \
    return array;\
}

#define FREE_ARRAY(TYPE) \
void free_array_##TYPE(struct array_##TYPE##_t *array){ \
   if(array == NULL) return;                            \
   free(array->data);    \
   free(array); \
}


#define SAVE_ARRAY(TYPE) \
int save_array_##TYPE(const struct array_##TYPE##_t *array, const char *filename){ \
    if(array == NULL || array->data == NULL || filename == NULL || array->size < 1 || array->capacity < 1 || array->capacity<array->size) return 1;                                \
    FILE * f = fopen(filename, "wb");                                              \
    if(f == NULL) return 2;                                                        \
    if(fwrite(&(array->size), sizeof(int), 1, f)!= (long unsigned int) 1){fclose(f); return 2;}\
    if(fwrite(array->data, sizeof(TYPE), array->size, f) != (long unsigned int) array->size){fclose(f); return 2;}                                                               \
    fclose(f);           \
    return 0;\
}

#define LOAD_ARRAY(TYPE) \
int load_array_##TYPE(struct array_##TYPE##_t **array, const char *filename){ \
    if(array == NULL || filename == NULL) return 1;                     \
    FILE * f = fopen(filename, "rb");                                   \
    if(f == NULL) return 2;                                                   \
    int res = 0;                     \
    int size = 0;\
    res = fread(&size, sizeof(int), 1, f);                                 \
    if(size < 1 || res != 1){fclose(f); return 3;}\
    *array = create_array_##TYPE(size);                          \
    if(*array == NULL){fclose(f); return 4;}                                  \
    res = fread((*array)->data, sizeof(TYPE), size, f);                    \
    if(res != size){fclose(f); free((*array)->data); free(*array); return 3;}\
    (*array)->size = size;                     \
    fclose(f);           \
    return 0;\
}

#define SORT_ARRAY(TYPE) \
int sort_array_##TYPE(struct array_##TYPE##_t *array){\
    if(array == NULL || array->data == NULL || array->size < 1 || array->capacity < 1 || array->capacity<array->size) return 1;      \
    TYPE temp;\
    for(int i = 0; i < array->size - 1; ++i)   \
        for(int j = 0; j < array->size - 1 - i; ++j) \
             if(*(array->data + j) > *(array->data + j + 1)){ \
                temp = *(array->data + j); \
                *(array->data + j) = *(array->data + j + 1);\
                *(array->data + j + 1) = temp;\
             }                           \
    return 0;                                    \
}

#endif //INC_15_FUNCTIONS_H