#include <stdio.h>

int main()
{
    int tab[11]={0,1,2,3,4,5,6,7,8,9,10};
    
    printf("%d %d %d %d %d %d %d %d %d %d %d\n", tab[0],tab[1],tab[2],tab[3],tab[4],tab[5],tab[6],tab[7],tab[8],tab[9],tab[10]);
    
    for(int i = 0;i<11;i++){
        printf("%d\n",tab[i]);
    }

    return 0;
}
