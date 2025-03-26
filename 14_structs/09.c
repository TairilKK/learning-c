#include <stdio.h>

struct point_t {
    int x;
    int y;
};

struct point_t* read(struct point_t* p);

int save_points_b(const char *filename, const struct point_t* p, unsigned int N);

int main() {
    int n;

    printf("Podaj liczbe punktow:");
    if(scanf("%d",&n)!=1){
        printf("Incorrect input");
        return 1;
    }
    if(n<1){
        printf("Incorrect input data");
        return 2;
    }
    if(n>100)
        n=100;
    struct point_t st[101];
    struct point_t *p=st;

    printf("Podaj punkty:");
    for(int i=0;i<n;i++){
        if(read(p+i)==NULL){
            printf("Incorrect input");
            return 1;
        }
    }
    char filename[31];
    printf("Podaj nazwĂÂ pliku:\n");
    scanf("%30s%*c",filename);

    int c=save_points_b(filename,p,n);

    if(c==2){
        printf("Couldn't create file");
        return 5;
    }


    printf("File saved");
    return 0;
}
struct point_t* read(struct point_t* p){
    if(p==NULL)
        return NULL;
    if(scanf("%d",&(p->x))!=1)
        return NULL;
    if(scanf("%d",&(p->y))!=1)
        return NULL;
    return p;
}
int save_points_b(const char *filename, const struct point_t* p, unsigned int N){
    if(filename==NULL||p==NULL||N==0)
        return 1;

    FILE *pFile=fopen(filename,"wb");
    if(pFile==NULL)
        return 2;

    if(fwrite(p,sizeof(int),N*2,pFile)!=N*2){
        fclose(pFile);
        return 3;
    }
    fclose(pFile);
    return 0;
}



