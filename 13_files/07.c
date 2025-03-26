#include <stdio.h>

int main() {
    char fname[31];
    printf("Podaj sciezke do pliku:");
    scanf("%30[^\n]s",fname);
    while(getchar()!='\n');

    FILE *pFile;
    pFile = fopen(fname,"r");

    if(pFile==NULL){
        printf("Couldn't open file");
        return 4;
    }
    fseek(pFile,0L,SEEK_SET);
    if(getc(pFile)==EOF){
        printf("file corrupted");
        fclose(pFile);
        return 6;
    }
    fseek(pFile, 0L, SEEK_END);

    long len = ftell(pFile);
    char let;
    long n, number;

    fseek(pFile,0,SEEK_SET);

    while(fgetc(pFile)!='\n'){
        fseek(pFile,-1,SEEK_CUR);
        if(fscanf(pFile,"%ld",&number)==0){
            printf("file corrupted");
            fclose(pFile);
            return 6;
        }
        n=ftell(pFile);
        if(number>=len){
            printf("file corrupted");
            fclose(pFile);
            return 6;
        }
        fseek(pFile,number,SEEK_SET);
        fscanf(pFile,"%c",&let);
        if(let>='0'&&let<='9'){
            printf("file corrupted");
            fclose(pFile);
            return 6;
        }
        fseek(pFile,n,SEEK_SET);
    }

    fseek(pFile,0,SEEK_SET);
    while(fgetc(pFile)!='\n'){
        fseek(pFile,-1,SEEK_CUR);
        fscanf(pFile,"%ld",&number);
        n=ftell(pFile);
        fseek(pFile,number,SEEK_SET);
        fscanf(pFile,"%c",&let);
        printf("%c",let);
        fseek(pFile,n,SEEK_SET);
    }

    fclose(pFile);

    return 0;
}

