#include <stdio.h>

int sum(const float* tab, unsigned int size, float *result);
int avg(const float* tab, unsigned int size, float *result);
int read_vector_float(float *vec, int size, float stop_value);
void display_vector(const float vec[], int size);

#define SIZE_VEC 101
#define STOP_VALUE 0

int main() {
   float T[SIZE_VEC];
   float res;

   printf("Podaj liczby:");
   int len=read_vector_float(T,SIZE_VEC-1,STOP_VALUE);
   if(len==-1){
       printf("Not enough data available");
       return 3;
   }
   if(len==-2){
        printf("Incorrect input");
       return 1;
   }
    if(*T==0){
        printf("Not enough data available");
        return 3;
    }



   if(sum(T,len,&res)){
       printf("Incorrect input");
       return 1;
   }
   printf("Suma: %.2f\n",res);

   if(avg(T,len,&res)){
       printf("Incorrect input");
       return 1;
   }
   printf("Srednia: %.2f",res);


    return 0;
}
int sum(const float* tab, unsigned int size, float *result){
    if(size<1||result==NULL||tab==NULL)
        return 1;

    *result=0;

    for(float* p=(float*)tab;p<tab+size;p++)
        *result+=*p;

    return 0;
}

int avg(const float* tab, unsigned int size, float *result){
    if(size<1||result==NULL||tab==NULL)
        return 1;

    sum(tab,size,result);
    *result/=(float)size;

    return 0;
}
int read_vector_float(float *vec, int size, float stop_value){
    int l=0;
    if(vec==NULL)
        return -1;
    for(float* p=vec; p<vec+size ;p++)   {
        if(scanf("%f",p)!= 1)
            return -2;
        else if(*p == stop_value)
            return l;
        l++;
    }
    if(l<1)
        return -1;
    else {
        while (getchar() != '\n');
        return l;
    }
}

void display_vector(const float* tab, int size){
    if(size>0){
        for(float* p=(float*)tab;p<tab+size;p++)
            printf("%.2f ",*p);
        printf("\n");
    }
}

