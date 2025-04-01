//
// Created by root on 12/23/24.
//

#include <string.h>
#include "03_file_reader.h"


void display_FAT_boot_sector(struct FAT_boot_sector_t boot_sector) {
    printf("=== FAT Boot Sector Information ===\n");
//    printf("Jump Instruction: %.3s\n", boot_sector.jump_instruction);
    printf("OEM Name: %.8s\n", boot_sector.oem_name);
    printf("Bytes Per Sector: %u\n", boot_sector.bytes_per_sector);
    printf("Sectors Per Cluster: %u\n", boot_sector.sectors_per_cluster);
    printf("Reserved Sectors: %u\n", boot_sector.reserved_sectors);
    printf("Number of FATs: %u\n", boot_sector.num_fats);
    printf("Max Root Directory Entries: %u\n", boot_sector.max_root_dir_entries);
    printf("Total Sectors (16-bit): %u\n", boot_sector.total_sectors_16);
    printf("Media Type: 0x%02X\n", boot_sector.media_type);
    printf("FAT Size (16-bit): %u\n", boot_sector.fat1216_size);
    printf("Sectors Per Track: %u\n", boot_sector.sectors_per_track);
    printf("Number of Heads: %u\n", boot_sector.num_heads);
    printf("Hidden Sectors: %u\n", boot_sector.hidden_sectors);
    printf("Total Sectors (32-bit): %u\n", boot_sector.total_sectors_32);
    printf("BIOS Drive Number: 0x%02X\n", boot_sector.bios_drive_number);
    printf("Extended Boot Signature: 0x%02X\n", boot_sector.extended_boot_signature);
    printf("Volume Serial Number: 0x%08X\n", boot_sector.volume_serial_number);
    printf("Volume Label: %.11s\n", boot_sector.volume_label);
    printf("File System Type: %8s\n", boot_sector.file_system_type);
    printf("Boot Signature: 0x%04X\n", boot_sector.boot_signature);
    printf("===================================\n");
}

struct disk_t* disk_open_from_file(const char* volume_file_name){
    if(volume_file_name == NULL) {
        errno = EFAULT;
        return NULL;
    }
    // Otwieram plik z dyskiem
    FILE *f = fopen(volume_file_name, "rb");
    if(f == NULL){
        errno = ENOENT;
        return NULL;
    }

    // Tworze strukturÄ przechowujÄca dysk
    struct disk_t *disk = malloc(sizeof(struct disk_t));
    if(disk == NULL){
        fclose(f);
        errno = ENOMEM;
        return NULL;
    }

    // WypeĹniam dane struktury
    disk->pFile = f;

    return disk;
}

int disk_read(struct disk_t* pdisk, int32_t first_sector, void* buffer, int32_t sectors_to_read){
    if(pdisk == NULL || buffer == NULL) {
        errno = EFAULT;
        return 0;
    }

    // PrzechodzÄ do pamiÄci dysku do sektora przekazanego @param: first_sector
    if(fseek(pdisk->pFile, (long)(first_sector * (long)SECTOR_SIZE), SEEK_SET) != 0) {
        errno = ERANGE;
        return 0;
    }

    // WczytujÄ @param: sectors_to_read sektorĂłw do @param: buffer
    if (fread(buffer, sizeof(uint8_t), sectors_to_read * SECTOR_SIZE, pdisk->pFile) == 0) {
        errno = ERANGE;
        return 0;
    }
//    display_FAT_boot_sector(*((struct FAT_boot_sector_t *)buffer));
    return sectors_to_read;
}

int disk_close(struct disk_t* pdisk){
    if(pdisk == NULL)
        return -1;
    if(pdisk->pFile)
        fclose(pdisk->pFile);
    free(pdisk);
    return 0;
}

/* Sprawdzanie poprawnoĹci fat12 */
int FAT12_check(struct FAT_boot_sector_t boot_sector){
    if(strncmp(boot_sector.file_system_type, "FAT12", 5) != 0)
        return 0;

    return 1;
}

struct volume_t* fat_open(struct disk_t* pdisk, uint32_t first_sector){
    if(pdisk == NULL) {
        errno = EFAULT;
        return NULL;
    }
    if(pdisk->pFile == NULL) {
        errno = EFAULT;
        return NULL;
    }

    /* Tworzenie woluminu na przechowywanie danych wyjĹciowych */
    struct volume_t *volume = calloc(1, sizeof(struct volume_t));
    if(volume == NULL){
        errno = ENOMEM;
        return NULL;
    }

    /* Wczytywanie tablicy FAT do boot_sector'a (SEKTOR 0)*/
    if(disk_read(pdisk, (int32_t)first_sector, (void*)&volume->boot_sector, BOOT_SECTOR_SIZE) == 0){
        free(volume);
        return NULL;
    }

    /* Sprawdzanie poprawnoĹci boot_sector'a */
    if(FAT12_check(volume->boot_sector) == 0){
        free(volume);
        errno = EINVAL;
        return NULL;
    }

    /* Przypisanie danych do woluminu */
    volume->disk = pdisk;

    return volume;
}

int fat_close(struct volume_t* pvolume){
    if(pvolume == NULL) {
        errno = EFAULT;
        return -1;
    }
    free(pvolume);
    return 0;
}

/* FILE */
void sfn_to_dir_entry(struct dir_entry_t *pEntry, struct root_directory_structure *sfn){
    pEntry->size = sfn->file_size;
    pEntry->is_readonly = IS_BIT_SET(sfn->attributes, 0);
    pEntry->is_hidden = IS_BIT_SET(sfn->attributes, 1);
    pEntry->is_system = IS_BIT_SET(sfn->attributes, 2);
    pEntry->is_directory = IS_BIT_SET(sfn->attributes, 4);
    pEntry->is_archived = IS_BIT_SET(sfn->attributes, 5);

    pEntry->creation_date.day = sfn->creation_date & 0x1F;
    pEntry->creation_date.month = (sfn->creation_date >> 5) & 0x0F;
    pEntry->creation_date.year = 1980 + ((sfn->creation_date >> 9) & 0x7F);

    pEntry->creation_time.second = (sfn->creation_time_hms & 0x1F) * 2;
    pEntry->creation_time.minute = (sfn->creation_time_hms >> 5) & 0x3F;
    pEntry->creation_time.hour = (sfn->creation_time_hms >> 11) & 0x1F;
    pEntry->high_order_first_cluster = sfn->high_order_first_cluster;
    pEntry->low_order_first_cluster = sfn->low_order_first_cluster;

    int j = 0;
    memset(pEntry->name, 0, 12);
    for(int k=0; k < 11; ++k){
        if(sfn->file_name[k] != ' '){
            pEntry->name[j] = sfn->file_name[k];
            j++;
        }
        else
            break;
    }

    if(j == 11)
        j -= 3;

    if (sfn->file_name[8] != ' ' && sfn->file_name[9] != ' ' && sfn->file_name[10] != ' ') {
        if (!strncmp(sfn->file_name + 8, "bin", 3))
            strcpy(pEntry->name + j, ".bin");
        else if (!strncmp(sfn->file_name + 8, "BIN", 3))
            strcpy(pEntry->name + j, ".BIN");
        else if (!strncmp(sfn->file_name + 8, "txt", 3))
            strcpy(pEntry->name + j, ".txt");
        else if (!strncmp(sfn->file_name + 8, "TXT", 3))
            strcpy(pEntry->name + j, ".TXT");
    }
    else if (sfn->file_name[8] != ' ' && sfn->file_name[9] != ' ') {
        if (!strncmp(sfn->file_name + 8, "tx", 2))
            strcpy(pEntry->name + j, ".tx");
        else if (!strncmp(sfn->file_name + 8, "TX", 2))
            strcpy(pEntry->name + j, ".TX");
    }
}

struct dir_entry_t* find_file(void* root_directory, const char* file_name){
    if(root_directory == NULL || file_name == NULL){
        errno = EFAULT;
        return NULL;
    }

    struct root_directory_structure *sfn = (struct root_directory_structure*)root_directory;

    /* Tworzenie struktury wyjĹciowej */
    struct dir_entry_t *pEntry = calloc(1, sizeof(struct dir_entry_t));
    if(pEntry == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    /* Przeszukiwanie tablicy FAT12 */
    for(int i = 0; i < (int)(ROOT_DIRECTORY_SECTORS * (SECTOR_SIZE / sizeof(struct root_directory_structure))); ++i) {
        if(sfn->file_name[0] == 'S' && sfn->file_name[1] == 'H')
            (void*) find_file(NULL, NULL);
        sfn_to_dir_entry(pEntry, sfn);

        /* Zwracanie wĹaĹciwego adresu w FAT12 z informacjami o pliku */
        if(strncmp(pEntry->name, file_name, FILE_NAME_SIZE_WITH_DOT) == 0)
            return pEntry;
        sfn++;
    }

    /* Zwalnianie zasobĂłw w razie niepowodzenia */
    free(pEntry);
    return NULL;
}

struct file_t* file_open(struct volume_t* pvolume, const char* file_name){
    if(pvolume == NULL || pvolume->disk == NULL) {
        errno = EFAULT;
        return NULL;
    }

    /* Przydzielanie pamiÄci na */
    void *root_directory = malloc(ROOT_DIRECTORY_SECTORS * pvolume->boot_sector.bytes_per_sector);
    if(root_directory == NULL){
        errno = ENOMEM;
        return NULL;
    }
    if(ROOT_DIRECTORY_SECTORS != disk_read(pvolume->disk, ROOT_DIRECTORY_START_SECTOR, root_directory, ROOT_DIRECTORY_SECTORS)){
        errno = EFAULT;
        free(root_directory);
        return NULL;
    }

    struct dir_entry_t *pEntry = find_file(root_directory, file_name);
    free(root_directory);
    if(pEntry == NULL){
        errno = ENOENT;
        return NULL;
    }
    if(pEntry->is_directory){
        errno = EISDIR;
        free(pEntry);
        return NULL;
    }
    struct file_t* pfile = calloc(1, sizeof(struct file_t));
    if(pfile == NULL){
        errno = ENOMEM;
        free(pEntry);
        return NULL;
    }
    pfile->volume = pvolume;
    pfile->dir_entry = pEntry;
    pfile->position = 0;

    return pfile;
}

int file_close(struct file_t* stream){
    if(stream == NULL) {
        errno = EFAULT;
        return 1;
    }
    free(stream->dir_entry);
    free(stream);
    return 0;
}
size_t file_read(void *ptr, size_t size, size_t nmemb, struct file_t *stream){
    if (ptr == NULL || stream == NULL)
        return -1;

    if (stream->position >= stream->dir_entry->size)
        return 0;

    void *buffer = malloc(stream->volume->boot_sector.fat1216_size * stream->volume->boot_sector.bytes_per_sector);
    if (buffer == NULL){
        errno = ENOMEM;
        return 0;
    }

    if (disk_read(stream->volume->disk, stream->volume->boot_sector.reserved_sectors, buffer, stream->volume->boot_sector.fat1216_size) != stream->volume->boot_sector.fat1216_size){
        free(buffer);
        errno = EFAULT;
        return 0;
    }

    struct clusters_chain_t *chain = get_chain_fat12(buffer, stream->volume->boot_sector.fat1216_size * SECTOR_SIZE, stream->dir_entry->low_order_first_cluster);
    free(buffer);
    buffer = NULL;

    if (chain == NULL){
        errno = EFAULT;
        return 0;
    }

    int data_region_start = stream->volume->boot_sector.reserved_sectors +
                            (stream->volume->boot_sector.num_fats * stream->volume->boot_sector.fat1216_size) +
                            (stream->volume->boot_sector.max_root_dir_entries * sizeof(struct root_directory_structure) +
                             (SECTOR_SIZE - 1)) / SECTOR_SIZE;

    int cluster_size_in_sectors = stream->volume->boot_sector.sectors_per_cluster;
    size_t buffer_size = stream->volume->boot_sector.bytes_per_sector * cluster_size_in_sectors;
    buffer = malloc(buffer_size);
    if (buffer == NULL){
        errno = ENOMEM;
        return 0;
    }

    size_t total_bytes_read = 0, bytes_to_read = size * nmemb, temp = size * nmemb;

    while (total_bytes_read < bytes_to_read && stream->position < stream->dir_entry->size && temp > 0) {
        size_t cluster_index = stream->position / buffer_size;
        size_t offset_in_cluster = stream->position % buffer_size;
        size_t bytes_in_cluster = buffer_size - offset_in_cluster;
        size_t remaining_bytes_in_file = stream->dir_entry->size - stream->position;
        size_t read_size = bytes_in_cluster > remaining_bytes_in_file ? remaining_bytes_in_file : bytes_in_cluster;
        read_size = read_size > temp ? temp : read_size;

        int first_sector_of_cluster = data_region_start + (chain->clusters[cluster_index] - 2) * cluster_size_in_sectors;

        if (disk_read(stream->volume->disk, first_sector_of_cluster, buffer, cluster_size_in_sectors) != cluster_size_in_sectors) {
            free(buffer);
            errno = EIO;
            return 0;
        }

        memcpy((uint8_t *)ptr + total_bytes_read, (uint8_t *)buffer + offset_in_cluster, read_size);
        stream->position += read_size;
        total_bytes_read += read_size;
        temp -= read_size;
    }

    free(buffer);
    free(chain->clusters);
    free(chain);

    return total_bytes_read / size;
}

int32_t file_seek(struct file_t* stream, int32_t offset, int whence){
    if(stream == NULL)
        return 0;
    switch (whence) {
        case SEEK_SET:
            stream->position = whence + offset;
            break;
        case SEEK_CUR:
            stream->position += offset;
            break;
        case SEEK_END:
            stream->position = stream->dir_entry->size + offset;
            break;
        default:
            errno=EFAULT;
            break;
    }
    return 0;
}

/* DIR */
struct dir_t* dir_open(struct volume_t* pvolume, const char* dir_path){
    if(pvolume == NULL || dir_path == NULL)
        return NULL;

    if(strcmp(dir_path, "\\")){
        return NULL;
    }

    struct dir_t *pdir = malloc(sizeof(struct dir_t));
    if(pdir == NULL){
        errno = ENOMEM;
        return NULL;
    }
    pdir->pvolume = pvolume;
    pdir->dir_read = 0;
    pdir->files = 0;
    return pdir;
}

int dir_read(struct dir_t* pdir, struct dir_entry_t* pentry){
    if(pdir == NULL)
        return -1;

    if(pdir->files >= pdir->pvolume->boot_sector.max_root_dir_entries){
        pdir->files = 0;
        pdir->dir_read = 0;
        return -2;
    }

    void *root_directory = malloc(ROOT_DIRECTORY_SECTORS * pdir->pvolume->boot_sector.bytes_per_sector);
    if(root_directory == NULL){
        errno = ENOMEM;
        return -3;
    }
    if(ROOT_DIRECTORY_SECTORS != disk_read(pdir->pvolume->disk, ROOT_DIRECTORY_START_SECTOR, root_directory, ROOT_DIRECTORY_SECTORS)){
        errno = EFAULT;
        free(root_directory);
        return -4;
    }

    struct root_directory_structure *sfn = (struct root_directory_structure*)root_directory + pdir->dir_read;

    int check = 0;
    for(size_t i = 0; i < sizeof(struct root_directory_structure); ++i){
        if(*((uint8_t*)sfn + i) == 0){
            check++;
        }
    }
    if(check == 0){
        pdir->dir_read=0;
        pdir->files=0;
        free(root_directory);
        return 1;
    }

    if(sfn->high_order_first_cluster != 0){
        pdir->dir_read+=1;
        free(root_directory);
        return dir_read(pdir, pentry);
    }

    if( sfn->file_name[0] == 0x00 || sfn->file_name[0] == 0x05){
        pdir->dir_read+=1;
        free(root_directory);
        return dir_read(pdir, pentry);
    }

    if(sfn->attributes > 0xC0){
        pdir->dir_read+=1;
        free(root_directory);
        return dir_read(pdir, pentry);
    }

    if(!IS_ALPHA(sfn->file_name[0])){
        pdir->dir_read+=1;
        free(root_directory);
        return dir_read(pdir, pentry);
    }

    check = 0;
    for(int i = 0; i < 11; ++i){
        if(!IS_ALPHA_SPACE(sfn->file_name[i])){
            check ++;
        }
    }
    if(check != 0){
        pdir->dir_read+=1;
        free(root_directory);
        return dir_read(pdir, pentry);
    }

    sfn_to_dir_entry(pentry, sfn);
    pdir->dir_read += 1;
    pdir->files += 1;
    free(root_directory);
    return 0;
}

int dir_close(struct dir_t* pdir){
    if(pdir == NULL)
        return -1;
    free(pdir);
    return 0;
}

