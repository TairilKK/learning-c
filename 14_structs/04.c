#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct point_t {
    int x;
    int y;
};

struct point_t* set(struct point_t* p, int x, int y);
void show(const struct point_t* p);
int save_point_t(const char *filename, const struct point_t* p);
int save_point_b(const char *filename, const struct point_t* p);
int load_point_b(const char *filename, struct point_t* p);
int load_point_t(const char *filename, struct point_t* p);

int main() {
    srand(time(NULL));

    struct point_t pt;
    struct point_t *p=&pt;

    //Wypelnienie struktury
    set(p,rand(),rand());

    //Wyswietlanie struktury
    show(p);
    //Pobieranie nazwy pliku
    char fname[31];
    char *filename=fname;
    printf("Podaj sciezke do pliku:\n");
    scanf("%30s%*c",filename);

    //Sprawdzenie rozszerzenia pliku
    if(strcmp(filename+strlen(filename)-4,".txt")==0){
        if(save_point_t(fname,p)==2){
            printf("couldn't create file");
            return 5;
        }
    }
    else if(strcmp(filename+strlen(filename)-4,".bin")==0){
        if(save_point_b(fname,p)==2)
        {
            printf("couldn't create file");
            return 5;
        }
    }
    else{
        printf("Unsupported file format");
        return 7;
    }
    //Otwieranie pliku
    printf("File saved\nDo you want to read the file (Y/N)?");
    char ans;
    scanf("%c",&ans);
    if(ans=='Y'||ans=='y'){
        if(strcmp(filename+strlen(filename)-4,".txt")==0){
            int ch = load_point_t(fname,p);
            if(ch==3){
                printf("File corrupted");
                return 6;
            }
            else if(ch==2){
                printf("Couldn't open file");
                return 4;
            }
            show(p);
        }
        else if(strcmp(filename+strlen(filename)-4,".bin")==0){
            int ch = load_point_b(fname,p);
            if(ch==3){
                printf("File corrupted");
                return 6;
            }
            else if(ch==2){
                printf("Couldn't open file");
                return 4;
            }
            show(p);
        }
    }
    else if(!(ans=='n'||ans=='N')){
        printf("Incorrect input");
        return 1;
    }
    return 0;
}
struct point_t* set(struct point_t* p, int x, int y){
    if(p==NULL)
        return NULL;
    p->x=x;
    p->y=y;
    return p;
}
void show(const struct point_t* p){
    if(p==NULL)
        return;
    printf("x = %d; y = %d\n",p->x,p->y);
}
int save_point_t(const char *filename, const struct point_t* p){
    if(filename==NULL||p==NULL)
        return 1;
    FILE *pFile= fopen(filename,"wt");
    if(pFile==NULL)
        return 2;
    fprintf(pFile,"%d %d",p->x,p->y);
    fclose(pFile);
    return 0;
}
int save_point_b(const char *filename, const struct point_t* p){
    if(filename==NULL||p==NULL)
        return 1;
    FILE *pFile= fopen(filename,"wb");
    if(pFile==NULL)
        return 2;
    fwrite(&(p->x),sizeof(int),1,pFile);
    //fwrite(" ",sizeof(char),1,pFile);
    fwrite(&(p->y),sizeof(int),1,pFile);
    fclose(pFile);
    return 0;
}
int load_point_b(const char *filename, struct point_t* p){
    if(filename==NULL||p==NULL)
        return 1;
    FILE *pFile= fopen(filename,"rb");
    if(pFile==NULL)
        return 2;
    if(fread(&(p->x),sizeof(int) ,1,pFile)!=1){
        fclose(pFile);
        return 3;
    }
    //fseek(pFile,1,SEEK_CUR);
    if(fread(&(p->y),sizeof(int) ,1,pFile)!=1){
        fclose(pFile);
        return 3;
    }
    fclose(pFile);
    return 0;
}
int load_point_t(const char *filename, struct point_t* p){
    if(filename==NULL||p==NULL)
        return 1;
    FILE *pFile= fopen(filename,"rt");
    if(pFile==NULL)
        return 2;
    if(fscanf(pFile,"%d %d",&(p->x),&(p->y))!=2) {
        fclose(pFile);
        return 3;
    }
    fclose(pFile);
    return 0;
}
