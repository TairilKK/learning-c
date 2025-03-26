#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

struct point_t {
    int x;
    int y;
};
struct segment_t {
    struct point_t start;
    struct point_t end;
};

struct point_t* set(struct point_t* p, int x, int y);
struct point_t* read(struct point_t* p);
void show(const struct point_t* p);

float distance(const struct point_t* p1, const struct point_t* p2, int *err_code);
void show_segment(const struct segment_t* p);
float length(const struct segment_t* s, int *err_code);

int main() {
    srand(time(NULL));
    struct segment_t pt;
    struct segment_t *p=&pt;

    printf("Podaj wspolrzedne pierwszego punktu:");

    if(read(&(p->start))==NULL){
        printf("Incorrect input");
        return 1;
    }
    if(read(&(p->end))==NULL){
        printf("Incorrect input");
        return 1;
    }

    int ec;
    show_segment(p);
    printf("%.2f",distance(&(p->start),&(p->end),&ec));
    return 0;
}
struct point_t* set(struct point_t* p, int x, int y){
    if(p==NULL)
        return NULL;
    p->x=x;
    p->y=y;
    return p;
}
struct point_t* read(struct point_t* p){
    if(p==NULL)
        return NULL;
    printf("Podaj x:");
    if(scanf("%d",&(p->x))!=1)
        return NULL;
    printf("Podaj y:");
    if(scanf("%d",&(p->y))!=1)
        return NULL;
    return p;
}
void show(const struct point_t* p){
    if(p==NULL)
        return;
    printf("%d %d\n",p->x,p->y);
}
float distance(const struct point_t* p1, const struct point_t* p2, int *err_code){
    if(err_code!=NULL)
        *err_code=1;
    if((p1==NULL||p2==NULL)||(p1->x==p2->x&&p1->y==p2->y))
        return -1;
    if(err_code!=NULL)
        *err_code=0;

    return sqrtf(((float)(p1->y)-(float)(p2->y))*((float)(p1->y)-(float)(p2->y))+((float)(p1->x)-(float)(p2->x))*((float)(p1->x)-(float)(p2->x)));
}
struct segment_t* read_segment(struct segment_t* p){
    if(p==NULL)
        return NULL;
    printf("Podaj wspolrzedne pierwszego punktu:");
    read(&(p->start));
    printf("Podaj wspolrzedne drugiego punktu:");
    read(&(p->end));

    return p;
}
void show_segment(const struct segment_t* p){
    if(p==NULL)
        return;
    show(&(p->start));
    show(&(p->end));
}
float length(const struct segment_t* s, int *err_code){
    if(s==NULL){
        if(err_code!=NULL)
            *err_code=1;
        return -1;
    }
    if(err_code!=NULL)
        *err_code=0;

    return distance(&(s->start),&(s->end),err_code);
}
