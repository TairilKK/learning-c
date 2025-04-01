//
// Created by jdobr on 24.08.2023.
//
#include <stdio.h>
#include <stdlib.h>

#include "09_image_utils.h"

/* ERROR CODE:
 * 1 - w przypadku błędnych danych wejściowych funkcji,
 * 2 - jeżeli nie udało się otworzyć pliku,
 * 3 - w przypadku kiedy plik jest uszkodzony, np. format jest niezgodny z oczekiwanym (nagłówek inny niż P2),
 * 4 - jeżeli nie uda się przydzielić pamięci.
 */
struct image_t* load_image_t(const char *filename, int *err_code) {
    if (!filename) {
        ERROR(1);
        return NULL;
    }

    FILE *f = fopen(filename, "r");
    if (!f) {
        ERROR(2);
        return NULL;
    }

    /* TYPE P2 */
    char c;
    fseek(f, 0, SEEK_SET);
    if ((c = (char) getc(f)) == EOF) {
        fclose(f);
        ERROR(3);
        return NULL;
    }
    if (c != 'P') {
        fclose(f);
        ERROR(3);
        return NULL;
    }
    if ((c = (char) getc(f)) == EOF) {
        fclose(f);
        ERROR(3);
        return NULL;
    }
    if (c != '2') {
        fclose(f);
        ERROR(3);
        return NULL;
    }
    if ((c = (char) getc(f)) == EOF) {
        fclose(f);
        ERROR(3);
        return NULL;
    }
    if (c != '\n') {
        fclose(f);
        ERROR(3);
        return NULL;
    }

    /* WIDTH and HEIGHT */
    int w = 0, h = 0;
    if (fscanf(f, "%d %d%c", &w, &h, &c) != 3) {
        fclose(f);
        ERROR(3);
        return NULL;
    }
    if (w < 1 || h < 1 || c != '\n') {
        fclose(f);
        ERROR(3);
        return NULL;
    }

    /* MAX */
    int max = 0;
    if (fscanf(f, "%d%c", &max, &c) != 2) {
        fclose(f);
        ERROR(3);
        return NULL;
    }
    if (max < 1 || max > 255 || c != '\n') {
        fclose(f);
        ERROR(3);
        return NULL;
    }

    /* STRUCT IMAGE_T CREATE */
    struct image_t *m = (struct image_t *) calloc(1, sizeof(struct image_t));
    if (!m) {
        fclose(f);
        ERROR(4);
        return NULL;
    }
    m->width = w;
    m->height = h;
    *(m->type + 0) = 'P';
    *(m->type + 1) = '2';
    *(m->type + 2) = '\0';

    m->ptr = (int **) calloc(m->height, sizeof(int *));
    if(!(m->ptr)){
        destroy_image(&m);
        fclose(f);
        ERROR(4);
        return NULL;
    }
    for(int i = 0; i < m->height; ++i){
        *(m->ptr + i) = (int *) calloc(m->width, sizeof (int));
        if(!*(m->ptr + i)){
            destroy_image(&m);
            fclose(f);
            ERROR(4);
            return NULL;
        }
    }

    /* READ FROM FILE TO STRUCT */
    for(int i = 0; i < m->height; ++i)
        for(int j = 0; j < m->width; ++j){
            if(fscanf(f, "%d", (*(m->ptr + i) + j)) != 1){
                destroy_image(&m);
                fclose(f);
                ERROR(3);
                return NULL;
            }
            c = fgetc(f);
            if(!(c == ' ' || c == '\n' || c == EOF) || *(*(m->ptr + i) + j) < 0 || *(*(m->ptr + i) + j) > max){
                destroy_image(&m);
                fclose(f);
                ERROR(3);
                return NULL;
            }
        }


    fclose(f);
    ERROR(0);
    return m;

}

/* RETURN value
 * 0 - w przypadku powodzenia operacji zapisu,
 * 1 - w przypadku błędnych danych wejściowych,
 * 2 - jeżeli nie udało się utworzyć pliku,
 * 3 - jeżeli nie udało się zapisać wszystkich danych do pliku.
 */
int save_image_t(const char * filename, const struct image_t *m1){
    if(!filename || !m1 || !(m1->ptr) || m1->height < 1 || m1->width < 1) return 1;

    FILE *f = fopen(filename, "w");
    if(!f) return 2;

    if(fprintf(f, "%s\n", m1->type) < 0) { fclose(f); return 3;}
    if(fprintf(f, "%d %d\n255\n", m1->width, m1->height) < 0) { fclose(f); return 3;}
    for(int i = 0; i < m1->height; ++i) {
        for (int j = 0; j < m1->width; ++j) {
            if(fprintf(f, "%d ", *(*(m1->ptr + i) + j)) < 0) { fclose(f); return 3;}
        }
        if(i != m1->height - 1)
        if(fprintf(f, "\n") < 0) { fclose(f); return 3;}
    }
    fclose(f);
    return 0;
}

const int* image_get_pixel(const struct image_t *img, int x, int y){
    if(!img || !img->ptr || img->height < 1 || img->width < 1 || y >= img->height || x >= img->width || x < 0 || y < 0) return NULL;
    return (const int *)(*(img->ptr + y) + x);
}
int* image_set_pixel(struct image_t *img, int x, int y){
    if(!img || !img->ptr || img->height < 1 || img->width < 1 || y >= img->height || x >= img->width || x < 0 || y < 0) return NULL;
    return (*(img->ptr + y) + x);
}

void destroy_image(struct image_t **m){
    if(!m || !(*m)) return;
    if(((*m)->ptr)) {
        for (int i = 0; i < (*m)->height; ++i)
            free(*((*m)->ptr + i));
        free((*m)->ptr);
    }
    free(*m);
    *m = NULL;
}

struct image_t* image_flip_horizontal(const struct image_t *m1){
    if(!m1 || !m1->ptr || m1->height<1 || m1->width < 1) return NULL;
    struct image_t *m = (struct image_t *) calloc(1, sizeof(struct image_t));
    if (!m)
        return NULL;

    m->width = m1->width;
    m->height = m1->height;
    *(m->type + 0) = 'P';
    *(m->type + 1) = '2';
    *(m->type + 2) = '\0';

    m->ptr = (int **) calloc(m->height, sizeof(int *));
    if(!(m->ptr)){
        destroy_image(&m);
        return NULL;
    }
    for(int i = 0; i < m->height; ++i){
        *(m->ptr + i) = (int *) calloc(m->width, sizeof (int));
        if(!*(m->ptr + i)){
            destroy_image(&m);
            return NULL;
        }
    }

    for(int i = 0; i < m->height; ++i)
        for(int j = 0; j < m->width; ++j)
            *(image_set_pixel(m, j, m->height - 1 - i)) = *(image_get_pixel(m1, j, i));


    return m;
}
struct image_t* image_flip_vertical(const struct image_t *m1){
    if(!m1 || !m1->ptr || m1->height<1 || m1->width < 1) return NULL;
    struct image_t *m = (struct image_t *) calloc(1, sizeof(struct image_t));
    if (!m)
        return NULL;

    m->width = m1->width;
    m->height = m1->height;
    *(m->type + 0) = 'P';
    *(m->type + 1) = '2';
    *(m->type + 2) = '\0';

    m->ptr = (int **) calloc(m->height, sizeof(int *));
    if(!(m->ptr)){
        destroy_image(&m);
        return NULL;
    }
    for(int i = 0; i < m->height; ++i){
        *(m->ptr + i) = (int *) calloc(m->width, sizeof (int));
        if(!*(m->ptr + i)){
            destroy_image(&m);
            return NULL;
        }
    }

    for(int i = 0; i < m->height; ++i)
        for(int j = 0; j < m->width; ++j)
            *(image_set_pixel(m, m->width - 1 - j, i)) = *(image_get_pixel(m1, j, i));


    return m;
}
struct image_t* image_negate(const struct image_t *m1){
    if(!m1 || !m1->ptr || m1->height<1 || m1->width < 1) return NULL;
    struct image_t *m = (struct image_t *) calloc(1, sizeof(struct image_t));
    if (!m)
        return NULL;

    m->width = m1->width;
    m->height = m1->height;
    *(m->type + 0) = 'P';
    *(m->type + 1) = '2';
    *(m->type + 2) = '\0';

    m->ptr = (int **) calloc(m->height, sizeof(int *));
    if(!(m->ptr)){
        destroy_image(&m);
        return NULL;
    }
    for(int i = 0; i < m->height; ++i){
        *(m->ptr + i) = (int *) calloc(m->width, sizeof (int));
        if(!*(m->ptr + i)){
            destroy_image(&m);
            return NULL;
        }
    }

    for(int i = 0; i < m->height; ++i)
        for(int j = 0; j < m->width; ++j) {
            *(image_set_pixel(m, j, i)) = 255;
            *(image_set_pixel(m, j, i)) -= *(image_get_pixel(m1, j, i));
        }
    return m;
}
