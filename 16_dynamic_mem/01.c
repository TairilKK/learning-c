#include <stdio.h>
#include <stdlib.h>

int main( )
{
    int *number;
    number = (int *) malloc(100*sizeof(int));

    if(number==NULL){
        printf("Failed to allocate memory");
        return 8;
    }

    for(int i=0;i<100;i++)
        *(number+i)=i;

    for(int i=0;i<100;i++)
        printf("%d ",*(number+i));

    free(number);
    return 0;
}
