//
// Created by jdobr on 24.08.2023.
//

#ifndef INC_07_IMAGE_UTILS_H
#define INC_07_IMAGE_UTILS_H

#define ERROR(error_code) do {if(err_code) *err_code = error_code; } while(0)

struct image_t {
    char type[3];
    int **ptr;
    int width;
    int height;
};

struct image_t* load_image_t(const char *filename, int *err_code);
int save_image_t(const char * filename, const struct image_t *m1);

void destroy_image(struct image_t **m);

const int* image_get_pixel(const struct image_t *img, int x, int y);
int* image_set_pixel(struct image_t *img, int x, int y);

int draw_image(struct image_t *img, const struct image_t *src, int destx, int desty);

#endif //INC_07_IMAGE_UTILS_H
