#include <stdio.h>


union bit_set{
    unsigned int u1;
    unsigned short u2[2];
    unsigned char u3[4];
};
int main() {
    union bit_set p;
    printf("Podaj liczbe:");

    if(scanf("%u",&(p.u1))!=1){
        printf("Incorrect input");
        return 1;
    }
    printf("%u\n%d %d\n%d %d %d %d\n",p.u1,*(p.u2),*(p.u2+1),*(p.u3),*(p.u3+1),*(p.u3+2),*(p.u3+3));
    for(int i=0;i<4;i++){
        printf("%d%d%d%d%d%d%d%d ",*(p.u3+i)/2/2/2/2/2/2/2%2,*(p.u3+i)/2/2/2/2/2/2%2,*(p.u3+i)/2/2/2/2/2%2,*(p.u3+i)/2/2/2/2%2,*(p.u3+i)/2/2/2%2,*(p.u3+i)/2/2%2,*(p.u3+i)/2%2,*(p.u3+i)%2);
    }


    return 0;
}