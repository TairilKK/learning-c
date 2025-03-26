#include <stdio.h>
#include "vector_utils.h"

int product_left(const long long *input, int input_size, long long *output, int output_size);
int product_right(const long long *input, int input_size, long long *output, int output_size);

#define LENGTH 10
#define STOP_VALUE (-1)


int main() {
   long long T[LENGTH];
   printf("Podaj liczby:\n");

   int c = read_vector_ll(T,LENGTH,STOP_VALUE);
   if(c==-2){
       printf("Incorrect input");
       return 1;
   }else if(c==-1||c==1||c==0){
       printf("Not enough data available");
       return 3;
   }
    long long T_outL[LENGTH];
    long long T_outR[LENGTH];

    product_right(T,c,T_outR,c);
    // display_vector_ll(T_outR,c);
    // printf("Prod R\n");
    product_left(T,c,T_outL,c);
    // display_vector_ll(T_outL,c);
    // printf("Prod L\n");

    for(int i=0;i<c;i++)
        *(T_outL+i)*=*(T_outR+i);

    display_vector_ll(T_outL,c);

    return 0;
}
int product_right(const long long *input, int input_size, long long *output, int output_size){
    if(input==NULL||output==NULL||input_size<2||output_size<2)
        return 1;

    for(long long *k=output+output_size-1;k>=output;k--) {
        *k=1;
        for(int i=output_size-1;i>k-output;i--)
            *k*=*(input+i);
    }
    return 0;
}
int product_left(const long long *input, int input_size, long long *output, int output_size){
    if(input==NULL||output==NULL||input_size<2||output_size<2)
        return 1;

    for(long long *k=output+output_size-1;k>=output;k--) {
        *k=1;
        for(int i=k-output-1;i>=0;i--)
            *k*=*(input+i);
    }
    return 0;
}

