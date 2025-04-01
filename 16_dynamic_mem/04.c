#include <stdio.h>
#include <stdlib.h>

int create_array_int(int **ptr, int N);
void destroy_array_int(int **ptr);

int main( )
{
    int n;
    printf("Podaj ilosc elementow:");
    if(scanf("%d",&n)!=1){
        printf("Incorrect input");
        return 1;
    }
    if(n<1){
        printf("Incorrect input data");
        return 2;
    }

    int *ptr;
    int **p=&ptr;

    create_array_int(p,n);

    if(p==NULL||*p==NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby:\n");

    for(int i=0;i<n;i++){
        if(scanf("%d",(*p+i))!=1){
            printf("Incorrect input");
            destroy_array_int(p);
            return 1;
        }
    }
    for(int i=n-1;i>=0;i--)
        printf("%d ",*(*p+i));

    destroy_array_int(p);

    return 0;
}

int create_array_int(int **ptr, int N){
    if(ptr==NULL||N<1)
        return 1;
    *ptr = (int*) calloc(N,sizeof(int));
    if(*ptr==NULL)
        return 2;
    return 0;
}
void destroy_array_int(int **ptr){
    if(ptr==NULL)
        return;
    if(*ptr!=NULL)
        free(*ptr);
    *ptr=NULL;
    ptr=NULL;
}
