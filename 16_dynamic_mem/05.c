#include <stdio.h>
#include <stdlib.h>

int* create_array_int(int N);
int* copy_array_int(const int* ptr, int N);
void display_array_int(const int* ptr, int N);

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
    int *p = create_array_int(n);

    if(p==NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby:\n");

    for(int i=0;i<n;i++){
        if(scanf("%d",(p+i))!=1){
            printf("Incorrect input");
            free(p);
            return 1;
        }
    }
    int *cp=copy_array_int(p,n);
    if(cp==NULL){
        free(p);
        printf("Failed to allocate memory");
        return 8;
    }
    display_array_int(p,n);
    display_array_int(cp,n);
    free(p);
    free(cp);

    return 0;
}

int* create_array_int(int N){
    if(N<1)
        return NULL;
    return (int*) malloc(N*sizeof(int));
}
void display_array_int(const int* ptr, int N){
    if(ptr==NULL||N<1)
        return;
    for(int i=0;i<N;i++)
        printf("%d ",*(ptr+i));
    printf("\n");
}
int* copy_array_int(const int* ptr, int N){
    if(ptr==NULL)
        return NULL;
    int *copy = create_array_int(N);
    if(copy==NULL)
        return NULL;
    for(int i=0;i<N;i++)
        *(copy+i)=*(ptr+i);
    return copy;
}
