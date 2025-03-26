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
    if(getc(pFile)==EOF)
        printf("nothing to show");

    for(int i=0;fgetc(pFile)!=EOF;i++){
        fseek(pFile,i,SEEK_SET);
        int c;
        c=fgetc(pFile);
        putc(c,stdout);

    }
    fclose(pFile);
    return 0;
}
