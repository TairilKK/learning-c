//
// Created by jdobr on 22.08.2023.
//

#ifndef INC_04_MATRIX_H
#define INC_04_MATRIX_H

#define ERROR(error_code) do{if(err_code) *err_code = error_code; } while(0)


struct matrix_t{
    int **ptr;
    int width;
    int height;
};

int matrix_create(struct matrix_t *m, int width, int height);
struct matrix_t* matrix_create_struct(int width, int height);
void matrix_destroy(struct matrix_t *m);
void matrix_destroy_struct(struct matrix_t **m);

void matrix_display(const struct matrix_t *m);

int matrix_read(struct matrix_t *m);
int matrix_save_b(const struct matrix_t *m, const char *filename);
int matrix_save_t(const struct matrix_t *m, const char *filename);

struct matrix_t* matrix_copy(const struct matrix_t *copy);
struct matrix_t* matrix_load_b(const char *filename, int *err_code);
struct matrix_t* matrix_load_t(const char *filename, int *err_code);

struct matrix_t* matrix_add(const struct matrix_t *m1, const struct matrix_t *m2);
struct matrix_t* matrix_subtract(const struct matrix_t *m1, const struct matrix_t *m2);
struct matrix_t* matrix_multiply(const struct matrix_t *m1, const struct matrix_t *m2);

#endif //INC_04_MATRIX_H
