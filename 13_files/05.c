#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    srand(time(NULL));
    int n;
    printf("Podaj liczbÄ liczb:\n");
    if(scanf("%d%*c",&n)==0){
        printf("Incorrect input");
        return 1;
    }
    if(n<1||n>1000){
        printf("Incorrect input data");
        return 2;
    }
    FILE *pFile;
    for(int i=0;i<n;i++){
        char filename[10]="00.txt";
        char *ptr = filename;
        if(i<100){
            *(ptr+1)=i/10%10+'0';
            for(int j=0;j<9;j++)
                *(ptr+j)=*(ptr+j+1);
        }else {
            *ptr = i / 100 % 10 + '0';
            *(ptr+1) = i /10% 10 + '0';
        }
        if(i%10==0)
            pFile = fopen(filename,"w");
        if(pFile==NULL){
            printf("Couldn't create file");
            return 5;
        }
        if(i%10==0) {
            printf("%s", filename);
            if(i+10<n)
                printf("\n");
        }
        fprintf(pFile,"%d\n",rand()%1001);
        if(i%10==9)
            fclose(pFile);
    }
    if(n%10!=0)
        fclose(pFile);
    return 0;
}

