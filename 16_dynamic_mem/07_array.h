#ifndef PRV_ARRAY_H

struct array_t
{
    int *ptr;
    int size;
    int capacity;
};

/* 40 06 */
int array_create(struct array_t *a, int N);
int array_push_back(struct array_t *a, int value);
void array_display(const struct array_t *a);
void array_destroy(struct array_t *a);

/* 40 07 */
int array_copy(const struct array_t *src, struct array_t *dest);
int array_separate(const struct array_t *a, struct array_t *odd, struct array_t *even);

#define PRV_ARRAY_H

#endif // PRV_ARRAY_H
