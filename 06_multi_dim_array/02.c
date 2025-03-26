#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    int macA[5][5];
    int macB[5][5];
    int macC[5][5]={0};
    srand(time(NULL));
    
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            macA[k][w]=rand()%10;
        }
    }
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            printf("%d ",macA[k][w]);
        }
        printf("\n");
    }
    
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            macB[k][w]=rand()%10;
        }
    }
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            printf("%d ",macB[k][w]);
        }
        printf("\n");
    }
  
    for(int w=0;w<4;w++){
        macC[w][w]=1;
    }
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            printf("%d ",macC[k][w]);
        }
        printf("\n");
    }
    return 0;
}
