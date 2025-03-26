#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int a, b=0, i = 0;
    while (i < 100)
    {
        a = rand() % 11 + 10;
        b += a;
        i++;
    }
    printf("%d ",b);
    return 0;
}
