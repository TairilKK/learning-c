#include <stdio.h>
#include <stdlib.h>

int sign(int value);

int main()
{
    int a;
    printf("podaj liczbe:");
    int c=scanf("%d",&a);
    
    switch(c)
    {
        case 1:
            switch(sign(a)){
                case 1: printf("positive");
                    break;
                case 0: printf("zero");
                    break;
                case -1: printf("negative");
                    break;
            }
            break;
        default:
            printf("incorrect input");
            return 1;
            break;
    }
    return 0;
}

int sign(int value){
    int ch;
    switch(value)
    {
        case 0:ch=0;
            break;
        default:
            ch=value/abs(value);
        break;
    }
    return ch;
}
