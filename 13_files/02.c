#include <stdio.h>

int file_size_from_path(const char *path);
int file_size_from_file(FILE *f);

int main() {
    char fname[31];
    printf("Podaj sciezke do pliku:\n");
    scanf("%30[^\n]s",fname);
    while(getchar()!='\n');

    int c=file_size_from_path(fname);
    FILE *pFile;
    pFile = fopen(fname,"r");
    if(pFile==NULL){
        printf("Couldn't open file");
        return 4;
    }
    int d = file_size_from_file(pFile);
    fclose(pFile);
    if(c==-1||d!=c){
        printf("Couldn't open file");
        return 4;
    }
    else if(c==-2)
        printf("Error");
    else
        printf("Rozmiar pliku wynosi %d bajtow",c);

    return 0;
}

int file_size_from_path(const char *path) {
    if (path == NULL)
        return -2;
    FILE *pFile;
    pFile = fopen(path, "r");
    if (pFile == NULL)
        return -1;
    int c = file_size_from_file(pFile);
    fclose(pFile);
    return c;
}
int file_size_from_file(FILE *f){
    if(f==NULL)
        return -2;
    int h = ftell(f);
    fseek(f,0,SEEK_END);
    int c = ftell(f);
    fseek(f,h,SEEK_SET);
    return c;
}
