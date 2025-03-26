#include <stdio.h>

int read_file(const char *filename);

int main() {
    char filename[31];
    printf("Podaj sciezke do pliku:\n");
    scanf("%30[^\n]s%*c",filename);

    int e=read_file(filename);
    if(e==-1||e==0){
        printf("Couldn't open file");
        return 4;
    }
    printf("%d",e);
    return 0;
}
int read_file(const char *filename){
    if(filename==NULL)//Poprawnosc *filename
        return -1;
    FILE *pFile;
    pFile = fopen(filename,"r");
    if(pFile==NULL)//Poprawnosc otwarcia pliku
        return 0;
    char fname[31];
    fseek(pFile,0,SEEK_SET);
    int c=1;
    while(fgetc(pFile)!=EOF) {
        int n;
        fseek(pFile,-1,SEEK_CUR);
        fscanf(pFile, "%30[^\n]c*c",fname);
        printf("%s\n",fname);
        n=read_file(fname);
        if(n!=-1) {
            c+=n;
        }
        if(fgetc(pFile)==EOF)
            break;
    }
    fclose(pFile);
    return c;
}
