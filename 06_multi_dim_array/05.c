#include <stdio.h>

#define WA 11
#define KA 11
#define WB 3
#define KB 3


int main()
{
        //ZMIENNE
    int macA[WA][KA];       //MACIERZ A
    int macB[WB][KB];   //MACIERZ B
    int c=0,c1=0;    //DO SPRAWDZENIA POPRAWNOSCI WCZYTANYCH DANYCH
    int ileB=0;
        //WCZYTYWANIE MACIERZY A
    printf("Podaj liczby:\n");
    for(int w=0;w<WA-1;w++){
        for(int k=0;k<KA-1;k++){
            c1++;
            c+=scanf("%d",&macA[w][k]);
            if(c!=c1){
                printf("incorrect input");
                return 1;
            }
        }
    }
        //WCZYTYWANIE MACIERZY B
    printf("Podaj liczby:\n");
    for(int w=0;w<WB-1;w++){
        for(int k=0;k<KB-1;k++){
            c1++;
            c+=scanf("%d",&macB[w][k]);
            if(c!=c1){
                printf("incorrect input");
                return 1;
            }
        }
    }
    int pom;
    for(int i=0;i<WB-1;i++){
        for(int j=0;j<KB-1;j++){
            
            for(int w=0;w<WA-2;w++){
                for(int k=0;k<KA-2;k++){
                    
                    if(macA[w][k]==macB[i][j]){
                        pom=0;
                        for(int n=0;n<2;n++){
                            for(int m=0;m<2;m++){
                                
                                if(macA[w+n][k+m]==macB[i+n][j+m])
                                    pom++;
                            }
                        }
                        if(pom==4){
                            ileB++;
                            printf("%d %d\n",k,w);
                        }
                    }
                }
            }
        }
    }
    printf("%d",ileB);


    return 0;
}
