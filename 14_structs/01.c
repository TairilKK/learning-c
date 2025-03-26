#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct point_t* set(struct point_t* p, int x, int y);
void show(const struct point_t* p);
struct point_t* read(struct point_t* p);
float distance(const struct point_t* p1, const struct point_t* p2, int *err_code);

struct point_t {
    int x;
    int y;
};

int main() {
    srand(time(NULL));
    int x,y;
    printf("Podaj wspĂłĹrzÄdnÄ x: ");
    if(scanf("%d",&x)==0){
        printf("Incorrect input");
        return 1;
    }
    printf("Podaj wspĂłĹrzÄdnÄ y: ");
    if(scanf("%d",&y)==0){
        printf("Incorrect input");
        return 1;
    }
    struct point_t P1;
    struct point_t P2;
    set(&P1,x,y);
    show(&P1);

    x=rand()%10;
    y=rand()%10;

    int ec;
    set(&P2,x,y);
    show(&P2);
    printf("%.2f", distance(&P1,&P2,&ec));

    return 0;
}

void show(const struct point_t* p){
    if(p!=NULL)
        printf("x = %d; y = %d\n",p->x,p->y);
}
struct point_t* set(struct point_t* p, int x, int y){
    if(p==NULL)
        return NULL;
    p->x = x;
    p->y = y;

    return p;
}
struct point_t* read(struct point_t* p){
    if(p==NULL)
        return NULL;
    printf("Podaj x:");
    scanf("%d",&(p->x));
    printf("Podaj y:");
    scanf("%d",&(p->y));
    return p;
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




