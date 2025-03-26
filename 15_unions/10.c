#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

struct bits{
    char bit0 : 1;
    char bit1 : 1;
    char bit2 : 1;
    char bit3 : 1;
    char bit4 : 1;
    char bit5 : 1;
    char bit6 : 1;
    char bit7 : 1;
};

union unia{
    char byte;
    struct bits bit;
};

int encode(const char *input, char *txt, const char *output);
int decode(const char * filename, char *txt, int size);


int main() {
    char operation;
    char inputFile[30];
    char outputFile[30];
    char input[1001];
    int res;

    printf("Do you want to encode (E/e) or decode (D/d) a message? ");

    if(scanf(" %c", &operation) != 1){
        printf("Incorrect input data");
        return 1;
    }
    if(operation == 'E' || operation == 'e'){
        printf("Enter a message to be encoded: ");
        scanf(" %1000[^\n]", input);
        while(getchar()!='\n');

        printf("Enter input file name: ");
        scanf(" %29[^\n]", inputFile);
        while(getchar()!='\n');

        printf("Enter output file name: ");
        scanf(" %29[^\n]", outputFile);
        while(getchar()!='\n');

        res = encode(inputFile, input, outputFile);
        if(res == 0) {
            printf("File saved");
            return 0;
        } else if(res == 2) {
            printf("couldn't open file");
            return 4;
        } else if(res == 4) {
            printf("couldn't create file");
            return 5;
        } else if(res == 3) {
            printf("File corrupted");
            return 6;
        }
    }
    else if (operation == 'D' || operation == 'd'){
        printf("Enter input file name: ");
        scanf(" %29[^\n]", inputFile);
        while(getchar()!='\n');

        res = decode(inputFile, input, 1001);
        if(res == 2) {
            printf("Couldn't open file");
            return 4;
        } else if(res == 3) {
            printf("File corrupted");
            return 6;
        }
        printf("%s", input);
        return 0;
    }
    else {
        printf("Incorrect input data");
        return 1;
    }
}

int decode(const char * filename, char *txt, int size){
    if(filename == NULL || txt == NULL || size < 1)
        return 1;

    FILE *f = fopen(filename, "r");
    if(f == NULL)
        return 2;

    int i = 0, j = 0;
    unsigned char r;
    union unia bfield, decode;
    decode.byte = 0;

    while(fgetc(f) != EOF && j < (size-1)){
        fseek(f, -1, SEEK_CUR);
        if(fscanf(f, "%hhu", &r) != 1){
            fclose(f);
            return 3;
        }
        bfield.byte = (char)r;

        if(i == 0)
            decode.bit.bit7 = bfield.bit.bit0;
        else if(i == 1)
            decode.bit.bit6 = bfield.bit.bit0;
        else if(i == 2)
            decode.bit.bit5 = bfield.bit.bit0;
        else if(i == 3)
            decode.bit.bit4 = bfield.bit.bit0;
        else if(i == 4)
            decode.bit.bit3 = bfield.bit.bit0;
        else if(i == 5)
            decode.bit.bit2 = bfield.bit.bit0;
        else if(i == 6)
            decode.bit.bit1 = bfield.bit.bit0;
        else if(i == 7)
            decode.bit.bit0 = bfield.bit.bit0;
        ++i;

        if(i==8){
            *(txt + j) = decode.byte;
            *(txt + j + 1 ) = '\0';
            ++j;
            i-=8;
        }
    }
    fclose(f);
    if(j == 0)
        return 3;
    return 0;
}

int encode(const char *input, char *txt, const char *output){
    if(input == NULL || txt == NULL || output == NULL)
        return 1;

    FILE *i = fopen(input, "r");
    if(i == NULL)
        return 2;

    FILE *o = fopen(output, "w");
    if(o == NULL){
        fclose(i);
        return 4;
    }

    int j = 0, it = 0;
    char t;
    unsigned char r;
    union unia bfield, decode;
    decode.byte = 0;

    while(fgetc(i) != EOF || *(txt + it) != '\0'){
        fseek(i, -1, SEEK_CUR);
        if(fscanf(i, "%hhu", &r) != 1){
            fclose(i);
            fclose(o);
            return 3;
        }
        decode.byte = (char) r;
        bfield.byte = 0;
        if (*(txt + it) != '\0')
            bfield.byte = *(txt + it);
        if (j == 0)
            decode.bit.bit0 = bfield.bit.bit7;
        else if (j == 1)
            decode.bit.bit0 = bfield.bit.bit6;
        else if (j == 2)
            decode.bit.bit0 = bfield.bit.bit5;
        else if (j == 3)
            decode.bit.bit0 = bfield.bit.bit4;
        else if (j == 4)
            decode.bit.bit0 = bfield.bit.bit3;
        else if (j == 5)
            decode.bit.bit0 = bfield.bit.bit2;
        else if (j == 6)
            decode.bit.bit0 = bfield.bit.bit1;
        else if (j == 7)
            decode.bit.bit0 = bfield.bit.bit0;
        ++j;

        fprintf(o, "%hhu", (unsigned char)decode.byte);
        t = (char)fgetc(i);
        if(t == '\n' || t == ' ' || t == EOF)
            fprintf(o, "%c", t);
        t = (char)fgetc(i);
        if(t == '\n' || t == EOF)
            fprintf(o, "%c", t);
        else if(t == '0' || t == '1' || t == '2' || t == '3' || t == '4' || t == '5' || t == '6'|| t == '7'|| t == '8'|| t == '9' )
            fseek(i, -1, SEEK_CUR);
        else{
            fclose(i);
            fclose(o);
            return 3;
        }
        if (j == 8) {
            if (*(txt + it) != '\0')
                ++it;
            j -= 8;
        }

    }

    fclose(i);
    fclose(o);

    if(*(txt + it) != '\0')
        return 3;

    return 0;
}

