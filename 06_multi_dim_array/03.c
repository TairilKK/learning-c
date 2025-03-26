#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    int macA[5][5];
    int macB[5][5];
    int macC[5][5]={0};
    int macApB[5][5];
    int macAmB[5][5];
    int macApBpC[5][5];
    int macAmBmC[5][5];
    int macmB[5][5];
    srand(time(NULL));
    //MACIERZ A
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
    //MACIERZ B
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
    //MACIERZ C
    for(int w=0;w<4;w++){
        macC[w][w]=1;
    }
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            printf("%d ",macC[k][w]);
        }
        printf("\n");
    }
    //MACIERZ A+B
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            macApB[k][w]=macA[k][w]+macB[k][w];
        }
    }
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            printf("%d ",macApB[k][w]);
        }
        printf("\n");
    }
    //MACIERZ A-B
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            macAmB[k][w]=macA[k][w]-macB[k][w];
        }
    }
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            printf("%d ",macAmB[k][w]);
        }
        printf("\n");
    }
    //MACIERZ A+B+C
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            macApBpC[k][w]=macA[k][w]+macB[k][w]+macC[k][w];
        }
    }
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            printf("%d ",macApBpC[k][w]);
        }
        printf("\n");
    }
    //MACIERZ A-B-C
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            macAmBmC[k][w]=macA[k][w]-macB[k][w]-macC[k][w];
        }
    }
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            printf("%d ",macAmBmC[k][w]);
        }
        printf("\n");
    }
    //MACIERZ -B
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            macmB[k][w]=0-macB[k][w];
        }
    }
    for(int w=0;w<4;w++){
        for(int k=0;k<4;k++){
            printf("%d ",macmB[k][w]);
        }
        printf("\n");
    }
    
        
    return 0;
}
