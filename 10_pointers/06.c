#include <stdio.h>


int main() {

   float T[100];
   int H;

   printf("Ile liczb chcesz wprowadzic?:");
   if(scanf("%d",&H)!=1){
       printf("Incorrect input");
       return 1;
   }
   else if(H<1||H>100){
       printf("Incorrect input data");
       return 2;
   }

   float sum=0;

   printf("Podaj liczby:");
   for(float* p=T;p<T+H;p++){
       if(scanf("%f",p)!=1){
           printf("Incorrect input");
           return 1;
       }
       sum+=*p;
   }
   for(float* p=T+H-1;p>=T;p--)
       printf("%f ",*p);

   printf("\nSuma: %.2f",sum);
   printf("\nSrednia: %.2f",sum/H);

    return 0;
}
