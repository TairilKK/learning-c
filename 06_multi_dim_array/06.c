#include <stdio.h>

int main()
{
    float tabp[11][11];
    float tabw[9][9];
    int c=0,c1=0;
    
    //Wczytywanie Tablicy PoczÄtkowej 10x10 tabp
    printf("podaj liczby:\n");
    for(int w=0;w<10;w++){
        for(int k=0;k<10;k++){
            c1++;
            c+=scanf("%f",&tabp[w][k]);
            if(c!=c1){
                printf("Incorrect input");
                return 1;
            }
        }
    }
    //Tworzenie Tablicy WyjĹciowej 8x8 tabw
    float suma;
    for(int w=1;w<9;w++){
        for(int k=1;k<9;k++){
            suma=0;
            for(int i=-1;i<2;i++){
                for(int j=-1;j<2;j++)
                   suma+=tabp[w+i][k+j];
            }
            tabw[w-1][k-1]=suma/9;
        }
    }
    for(int w=0;w<8;w++){
        for(int k=0;k<8;k++)
            printf("%.2f ",tabw[w][k]);
        printf("\n");
    }

    return 0;
}
