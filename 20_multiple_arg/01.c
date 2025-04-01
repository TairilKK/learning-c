#include <stdio.h>
#include <stdarg.h>

int stats(int *sum, float *avg, int num,...) ;

int main() {
    int sum, num;
    float avg;

    printf("Enter number of elements: ");

    if(scanf("%d", &num)!=1){
        printf("Incorrect input");
        return 1;
    }
    if(num<=0 || num>3){
        printf("Incorrect input data");
        return 2;
    }

    int arg[] = {0, 0,0};

    printf("Enter numbers: ");
    for (int i = 0; i < num; ++i){
        if(scanf("%d", &arg[i])!=1){
            printf("Incorrect input");
            return 1;
        }
    }

    stats(&sum, &avg, num, arg[0], arg[1], arg[2]);
    printf("%d %f", sum, avg);

    return 0;
}

int stats(int *sum, float *avg, int num,...){
    if(sum==NULL || avg == NULL || num<=0 )
        return 1;

    va_list args;
    va_start(args, num);

    int arg;

    *sum = 0;
    *avg = 0.0f;

    for(int i = 0; i<num; ++i){
        arg = va_arg(args, int);
        *sum += arg;
    }
    *avg = (float)(*sum) / (float)num;

    va_end(args);

    return 0;
}
