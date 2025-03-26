#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int a, i = 0;
    while (i<10)
    {
        a = rand()%11+10;
        printf("%d ", a);
        i++;
    }
    return 0;
}
