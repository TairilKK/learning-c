#include <stdio.h>
#include <stdlib.h>

int main( )
{
    float *number;
    number = (float *) malloc(sizeof(float));

    if(number==NULL){
        printf("Failed to allocate memory");
        return 8;
    }

    *number=3.141593;

    printf("%f %p",*number,(void*)number);

    free(number);
    return 0;
}
