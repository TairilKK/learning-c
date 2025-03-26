#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));

        int a = rand()%11+30;
        printf("%d ", a);
    return 0;
}
