#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int a;
    do {
    a = rand()&2001-1000;
    printf("%d\n", a);
    }
    while(a<100 || a>200);

    return 0;
}
