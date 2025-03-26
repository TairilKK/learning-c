#include <stdio.h>

int is_balanced(unsigned long long a);

int main() {
    unsigned long long a;
    printf("Podaj liczbe:");
    if(scanf("%llu",&a)!=1) {
        printf("Incorrect input");
        return 1;
    }
    while(is_balanced(++a)==0);


    printf("%llu",a);

    return 0;
}
int is_balanced(unsigned long long a){
    int p=0, np=0;
    for (int i=1; i < (int)a+1; i++) {
        if (a % i == 0) {
            if(i%2==1) {
                np++;
            }
            else {
                p++;
            }
        }
    }
    if(p==np)
        return 1;
    else
        return 0;
}
