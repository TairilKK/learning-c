#include <stdio.h>

int main() {
    char fname[31];
    printf("Podaj sciezke do pliku:\n");
    scanf("%30[^\n]s",fname);
    while(getchar()!='\n');

    FILE *pFile;
    pFile = fopen(fname,"r");

    if(pFile==NULL){
        printf("Couldn't open file");
        return 4;
    }
    printf("Podaj sciezke do pliku wyjsciowego:\n");
    scanf("%30[^\n]s",fname);
    while(getchar()!='\n');

    FILE *pFile_o;
    pFile_o = fopen(fname,"wt");

    if(pFile_o==NULL){
        printf("Couldn't create file");
        fclose(pFile);
        return 5;
    }
    for(int i=0;fgetc(pFile)!=EOF;i++){
        fseek(pFile,-1-i,SEEK_END);
        int c;
        c=fgetc(pFile);
        fputc(c,pFile_o);
        fseek(pFile,i+1,SEEK_SET);
    }
    printf("File copied");

    fclose(pFile);
    fclose(pFile_o);
    return 0;
}

