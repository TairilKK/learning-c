#include <stdio.h>

int swap(int*, int*);

int main() {
    int a,b;
    int *a1,*b1;

    a1=&a;
    b1=&b;

    printf("Wpisz 2 liczby int oddzielajac spacja\n");

    if(scanf("%d %d",a1, b1)!=2){
        printf("Incorrect input");
        return 1;
    }
    swap(a1,b1);

    printf("%d %d",*a1,*b1);


    return 0;
}
int swap(int* a, int* b){
    if(a==NULL||b==NULL)
        return 1;
    int ch = *a;
    *a=*b;
    *b=ch;
    return 0;
}
