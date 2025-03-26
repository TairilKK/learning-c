#include <stdio.h>

int compare(int, int, int);

int main()
{
    int a,b,c;
    printf("podaj trzy liczby: ");
    int z=scanf("%d-%d-%d",&a,&b,&c);
    if(z!=3){
        printf("incorrect input"); 
        return 1;
    }
    if(compare(a,b,c)==0)
        printf("NOT EQUAL");
    else
        printf("EQUAL");

    return 0;
}
int compare(int a, int b, int c){
    if(a==b && b==c)
        return 1;
    else
        return 0;
}
