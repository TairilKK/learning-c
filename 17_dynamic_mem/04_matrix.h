//
// Created by jdobr on 22.08.2023.
//

#ifndef INC_04_MATRIX_H
#define INC_04_MATRIX_H

struct matrix_t{
    int **ptr;
    int width;
    int height;
};

int matrix_create(struct matrix_t *m, int width, int height);
int matrix_read(struct matrix_t *m);
void matrix_display(const struct matrix_t *m);
void matrix_destroy(struct matrix_t *m);

#endif //INC_04_MATRIX_H
