//
// Created by jdobr on 24.08.2023.
//

#ifndef INC_03_ARRAY_2D_H
#define INC_03_ARRAY_2D_H

int create_array_2d_2(int ***ptr, int width, int height);
void destroy_array_2d(int ***ptr, int height);
void display_array_2d(int **ptr, int width, int height);
int sum_array_2d(int **ptr, int width, int height);
int sum_row(int *ptr, int width);

#endif //INC_03_ARRAY_2D_H
