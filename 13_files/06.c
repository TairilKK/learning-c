#include <stdio.h>

int main() {
    char filename[31];
    printf("Podaj sciezke do pliku:\n");
    scanf("%30[^\n]s%*c",filename);

    FILE *pFile;
    pFile = fopen(filename,"r");

    if(pFile==NULL) {
        printf("COULDN'T OPEN FILE");
        return 4;
    }
    if(fgetc(pFile)==EOF){
        printf("NOTHING TO SHOW");
        fclose(pFile);
        return 0;
    }
    fseek(pFile,0,SEEK_SET);
    while(fgetc(pFile)!=EOF){
        fseek(pFile,-1, SEEK_CUR);
        int buff = fgetc(pFile);
        if(buff>='a'&&buff<='z') {
            printf("%c",buff-'a'+'A');
        }
        else {
            printf("%c",buff);
        }
    }
    fclose(pFile);
    return 0;
}
