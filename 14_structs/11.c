#include <stdio.h>
#include <string.h>


#define MAX_FILE_NAME_LENGTH 1000
#define MAX_FILES 5
#define MAX_TEXT_LENGTH 1000

struct file_t
{
    FILE *f;
    int size;
};

int open_file(struct file_t* f, const char *filename);
struct file_t* find_min(const struct file_t* files, int size);
void close_file(struct file_t* f);

int main() {
    struct file_t files[MAX_FILES];
    struct file_t * min_file;

    char filename[MAX_FILE_NAME_LENGTH];
    char temp = ' ';
    int i, files_counter = 0;

    /* WCZYTYWANIE NAZWY PLIKU */

    printf("Podaj nazwy plikow: \n");
    while(files_counter <= MAX_FILES)
    {
        i = 0;
        temp = (char)getchar();
        if (temp == '\n')
            break;
        else
        {
            *filename = temp;
            *(filename + 1 )= '\0';
            i++;
        }
        while (i < MAX_FILE_NAME_LENGTH - 1) {
            temp = (char) getchar();
            if (temp == '\n')
                break;
            *(filename + i) = temp;
            *(filename + i + 1 )= '\0';
            ++i;
        }
        if(open_file((files + files_counter), filename)==0) {
            ++files_counter;
        }
    }

    if(files_counter == 0){
        printf("Couldn't open file");
        return 4;
    }

    /* POBIERANIE TEKSTOW */

    printf("Podaj teksty: \n");
    while(1)
    {
        i = 0;
        temp = (char)getchar();
        if (temp == '\n')
            break;
        else
        {
            *filename = temp;
            *(filename + 1 )= '\0';
            i++;
        }
        while (i < MAX_TEXT_LENGTH - 1) {
            temp = (char) getchar();
            *(filename + i) = temp;
            *(filename + i + 1 )= '\0';
            ++i;
            if (temp == '\n')
                break;
        }
        min_file = find_min(files, files_counter);
        fprintf(min_file->f, "%s", filename);
        min_file->size += strlen(filename);
    }

    /* ZAMYKANIE PLIKOW */

    for(int index = 0; index < files_counter; close_file(files + index), ++index);

    printf("File saved");
    return 0;
}

int open_file(struct file_t* f, const char *filename){
    if(f == NULL || filename == NULL)
        return 1;

    FILE *pFile;
    pFile = fopen(filename, "a");
    if(pFile == NULL)
        return 2;

    f->size = ftell(pFile);
    f->f = pFile;
    return 0;
}

void close_file(struct file_t* f){
    if(f == NULL || f->f == NULL)
        return;
    fclose(f->f);
}

struct file_t* find_min(const struct file_t* files, int size){
    if(files == NULL || size<1)
        return NULL;

    struct file_t* pf_min = (struct file_t*)files;

    for(int i = 0; i<size; ++i)
        if((files+i)->size < pf_min->size)
            pf_min = (struct file_t*)(files + i);

    return pf_min;
}



