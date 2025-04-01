//
// Created by jdobr on 24.08.2023.
//
#include <stdio.h>
#include <stdlib.h>

#include "image_utils.h"

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

int draw_image(struct image_t *img, const struct image_t *src, int destx, int desty){
    if(!img || !img->ptr || img->height < 1 || img->width < 1 || src->height < 1 || src->width < 1 || img->height <= (desty + src->height - 1) || img->width <= (destx + src->width - 1) || desty < 0 || destx < 0) return 1;

    for(int i = 0; i < src->height; ++i)
        for(int j = 0; j < src->width; j++)
            *(image_set_pixel(img, destx + j, desty + i)) = *(image_get_pixel(src, j, i));

    return 0;
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

// 08
int image_draw_rectangle(struct image_t *img, const struct rectangle_t *rect, int value){
    if(!img || !img->ptr || !rect || value < 0 || value > 255) return 1;
    if(rect->p.x < 0 || rect->p.y < 0) return 1;
    if(rect->p.x >= img->width || rect->width < 1|| (rect->p.x + rect->width - 1) > img->width) return 1;
    if(rect->p.y >= img->height || rect->height < 1 || (rect->p.y + rect->height - 1) > img->height) return 1;

    for(int i = 0; i < rect->width; ++i){
        *(image_set_pixel(img,rect->p.x + i, rect->p.y)) = value;
        *(image_set_pixel(img,rect->p.x + i, rect->p.y + rect->height - 1)) = value;
    }

    for(int i = 0; i < rect->height - 1; ++i){
        *(image_set_pixel(img,rect->p.x, rect->p.y + i)) = value;
        *(image_set_pixel(img,rect->p.x + rect->width - 1, rect->p.y + i)) = value;
    }
    return 0;
}