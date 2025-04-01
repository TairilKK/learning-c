#include <stdio.h>
#include <stdlib.h>

void *concat_zip(const void * const float_buffer,
                 const void * const int16_t_buffer,
                 int size);

void display_float_short(const void* array, int size){
    if(array==NULL)
        return;

    for(int i = 0; i<size/2; i++)
        printf("%f %d "
               , *((float*)((u_int8_t*)array + i * (sizeof(float)+sizeof(int16_t))))
               , *((int16_t*)((u_int8_t*)array + i * (sizeof(float)+sizeof(int16_t)) + sizeof(float))));

}

int main(void) {
    float f_array[] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    int16_t i_array[] ={0,1,2,3,4};

    void * res = concat_zip((void*)f_array, (void*)i_array, 5);

    display_float_short(res, 10);

    free(res);
    return 0;
}

void *concat_zip(const void * const float_buffer, const void * const int16_t_buffer, int size){
    if(float_buffer == NULL || int16_t_buffer == NULL || size < 1)
        return NULL;

    void* array = (void*) malloc(size * (sizeof(int16_t) + sizeof(float)));
    if(array==NULL)
        return NULL;

    float * f_ptr = (float*)float_buffer;
    int16_t * i_ptr = (int16_t*)int16_t_buffer;

    for(int i = 0; i<size; ++i){
        *((float*) ((u_int8_t*)array + i * (sizeof(float) + sizeof(int16_t)))) = *(f_ptr + i);
        *((int16_t*) ((u_int8_t*)array + i * (sizeof(float) + sizeof(int16_t))+ sizeof(float))) = *(i_ptr + i);
    }

    return array;
}