#include <stdio.h>


union bit_set{
    unsigned int u1;
    unsigned char u3[4];
};
int main() {
    union bit_set p;
    printf("Podaj liczbe:");

    if(scanf("%u",&(p.u1))!=1){
        printf("Incorrect input");
        return 1;
    }
    int sum=0;
    for(int i=0;i<4;i++){
        sum+=*(p.u3+i)/2/2/2/2/2/2/2%2+*(p.u3+i)/2/2/2/2/2/2%2+*(p.u3+i)/2/2/2/2/2%2+*(p.u3+i)/2/2/2/2%2+*(p.u3+i)/2/2/2%2+*(p.u3+i)/2/2%2+*(p.u3+i)/2%2+*(p.u3+i)%2;
    }
    if(sum%2)
        printf("NO");
    else
        printf("YES");


    return 0;
}