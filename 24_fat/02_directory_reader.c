//
// Created by jdobr on 23.12.2024.
//

#include "02_directory_reader.h"
#include <string.h>

#define NAME_SEPARATOR ' '
#define IS_BIT_SET(value, bit) (((value) & (1 << (bit))) ? 1 : 0)
#define IS_ALPHA(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

FILE *pFile = NULL;

void display_sfn(struct root_directory_structure r){
    printf("File Name: ");
    for(size_t i = 0; i < 11; ++i)
        putchar(r.file_name[i]);

    putchar('\n');
//    printf("Status: 0x%02X\n", r.status);
    printf("Attributes: 0x%02X\n", r.attributes);
    printf("Reserved: 0x%02X\n", r.reserved);
    printf("Creation Time: Timestamp: %u, HMS: 0x%04X\n", r.creation_time_ts, r.creation_time_hms);
    printf("Creation Date: 0x%04X\n", r.creation_date);
    printf("Access Date: 0x%04X\n", r.access_date);
    printf("High-Order First Cluster: 0x%04X\n", r.high_order_first_cluster);
    printf("Modified Time: 0x%04X\n", r.modified_time);
    printf("Modified Date: 0x%04X\n", r.modified_date);
    printf("Low-Order First Cluster: 0x%04X\n", r.low_order_first_cluster);
    printf("File Size: %u bytes\n", r.file_size);
}

void display_entry_long(struct dir_entry_t entry) {
    printf("File Name: %s\n", entry.name);
    printf("File Size: %zu bytes\n", entry.size);

    printf("Attributes:\n");
    printf("  Archived: %s\n", entry.is_archived ? "Yes" : "No");
    printf("  Read-only: %s\n", entry.is_readonly ? "Yes" : "No");
    printf("  System: %s\n", entry.is_system ? "Yes" : "No");
    printf("  Hidden: %s\n", entry.is_hidden ? "Yes" : "No");
    printf("  Directory: %s\n", entry.is_directory ? "Yes" : "No");

    printf("Creation Date: %02d/%02d/%04d\n",
           entry.creation_date.day,
           entry.creation_date.month,
           entry.creation_date.year);

    printf("Creation Time: %02d:%02d:%02d\n",
           entry.creation_time.hour,
           entry.creation_time.minute,
           entry.creation_time.second);
}

struct dir_entry_t *read_directory_entry(const char *filename) {
    if (filename == NULL && pFile == NULL)
        return NULL;

    if (filename != NULL && pFile != NULL) {
        fclose(pFile);
        pFile = NULL;
    }

    if (filename != NULL) {
        pFile = fopen(filename, "rb");
        if (pFile == NULL) {
            return NULL;
        }
    }

    struct root_directory_structure sfn;
    do {
        if (feof(pFile)) {
            fclose(pFile);
            pFile = NULL;
            return NULL;
        }

        if (fread(&sfn, sizeof(struct root_directory_structure), 1, pFile) == 0)
            return NULL;

        // pusty wpis
        if (sfn.file_name[0] == 0) {
            fclose(pFile);
            pFile = NULL;
            return NULL;
        }
    }while(!IS_ALPHA(sfn.file_name[0]));
//    else if(!IS_ALPHA(sfn.file_name[0]))
//        return read_directory_entry(NULL);

//    display_sfn(sfn);
//    printf("\n\n");
    struct dir_entry_t *pEntry = calloc(1, sizeof(struct dir_entry_t));
    if(pEntry == NULL)
        return NULL;


    pEntry->size = sfn.file_size;

    pEntry->is_readonly = IS_BIT_SET(sfn.attributes, 0);
    pEntry->is_hidden = IS_BIT_SET(sfn.attributes, 1);
    pEntry->is_system = IS_BIT_SET(sfn.attributes, 2);
    pEntry->is_directory = IS_BIT_SET(sfn.attributes, 4);
    pEntry->is_archived = IS_BIT_SET(sfn.attributes, 5);

    pEntry->creation_date.day = sfn.creation_date & 0x1F;
    pEntry->creation_date.month = (sfn.creation_date >> 5) & 0x0F;
    pEntry->creation_date.year = 1980 + ((sfn.creation_date >> 9) & 0x7F);

    pEntry->creation_time.second = (sfn.creation_time_hms & 0x1F) * 2;
    pEntry->creation_time.minute = (sfn.creation_time_hms >> 5) & 0x3F;
    pEntry->creation_time.hour = (sfn.creation_time_hms >> 11) & 0x1F;


    int j = 0;
    for(int i=0; i<11; ++i){
        if(sfn.file_name[i] != ' '){
            pEntry->name[j] = sfn.file_name[i];
            j++;
        }
        else
            break;
    }

    if(j == 11)
        j -= 3;

    if(!strncmp(sfn.file_name+8, "bin", 3))
        strcpy(pEntry->name + j, ".bin");

    else if(!strncmp(sfn.file_name+8, "BIN", 3))
        strcpy(pEntry->name + j, ".BIN");

    else if(!strncmp(sfn.file_name+8, "txt", 3))
        strcpy(pEntry->name + j, ".txt");

    else if(!strncmp(sfn.file_name+8, "TXT", 3))
        strcpy(pEntry->name + j, ".TXT");


    return pEntry;
}


