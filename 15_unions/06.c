#include <stdio.h>

union double_to_char_t {
    double d;
    char tab[8];
};

int save_double(const union double_to_char_t *dtc, const char *filename);
int load_double(union double_to_char_t *dtc, const char *filename);

int main() {
    union double_to_char_t p;
    union double_to_char_t *dtc=&p;
    printf("Podaj liczbe:");
    if(scanf("%lf",&(p.d))!=1){
        printf("Incorrect input");
        return 1;
    }
    char filename[40];
    printf("Podaj nazwe pliku:");
    scanf("%39s%*c",filename);
    int c=save_double(dtc,filename);
    if(c==2){
        printf("Couldn't create file");
        return 5;
    }

    printf("File saved\n");

    printf("Podaj nazwe pliku:");
    scanf("%39s%*c",filename);
    c=load_double(dtc,filename);
    if(c==2){
        printf("Couldn't open file");
        return 4;
    }
    else if(c==3){
        printf("File corrupted");
        return 6;
    }
    printf("%lf",p.d);
    return 0;
}
int save_double(const union double_to_char_t *dtc, const char *filename){
    if(dtc==NULL||filename==NULL)
        return 1;
    FILE *pFile=fopen(filename,"wt");
    if(pFile==NULL)
        return 2;
    int c=fprintf(pFile,"%c%c%c%c%c%c%c%c",*(dtc->tab),*(dtc->tab+1),*(dtc->tab+2),*(dtc->tab+3),*(dtc->tab+4),*(dtc->tab+5),*(dtc->tab+6),*(dtc->tab+7));
    fclose(pFile);
    if(c!=8)
        return 3;
    return 0;
}
int load_double(union double_to_char_t *dtc, const char *filename){
    if(dtc==NULL||filename==NULL)
        return 1;
    FILE *pFile=fopen(filename,"rt");
    if(pFile==NULL)
        return 2;
    int c=fscanf(pFile,"%c%c%c%c%c%c%c%c",(signed char*)(dtc->tab),(signed char*)(dtc->tab+1),(signed char*)(dtc->tab+2),(signed char*)(dtc->tab+3),(signed char*)(dtc->tab+4),(signed char*)(dtc->tab+5),(signed char*)(dtc->tab+6),(signed char*)(dtc->tab+7));
    fclose(pFile);
    if(c!=8)
        return 3;
    return 0;
}
