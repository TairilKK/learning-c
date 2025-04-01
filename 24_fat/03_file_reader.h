//
// Created by root on 12/23/24.
//

#ifndef PROJECT1_FILE_READER_H
#define PROJECT1_FILE_READER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

#include "03_directory_reader.h"

#define BOOT_SECTOR_SIZE ((int32_t)1)

#define FAT_PRIMARY_START_SECTOR 1
#define FAT_PRIMARY_END_SECTOR 9
#define FAT_SECONDARY_START_SECTOR 10
#define FAT_SECONDARY_END_SECTOR 18
#define FAT_SECTORS \
    (FAT_SECONDARY_END_SECTOR - FAT_PRIMARY_START_SECTOR + 1)

#define ROOT_DIRECTORY_START_SECTOR 19
#define ROOT_DIRECTORY_END_SECTOR 32
#define ROOT_DIRECTORY_SECTORS \
    (ROOT_DIRECTORY_END_SECTOR - ROOT_DIRECTORY_START_SECTOR + 1)

#define DATA_START (ROOT_DIRECTORY_END_SECTOR + 1)

#define SECTOR_SIZE 512

#define FILE_NAME_SIZE 11
#define FILE_NAME_SIZE_WITH_DOT (FILE_NAME_SIZE + 1)

struct disk_t
{
    FILE *pFile;
};

struct FAT_boot_sector_t
{

    /* bytes: 0 - 35 */
    char jump_instruction[3];      // 0-2:   Instrukcja skoku do kodu bootujÄcego
    char oem_name[8];              // 3-10:  Nazwa OEM w ASCII
    uint16_t bytes_per_sector;     // 11-12: Bajty na sektor
    uint8_t sectors_per_cluster;   // 13:    Sektory na klaster
    uint16_t reserved_sectors;     // 14-15: Rozmiar zarezerwowanego obszaru w sektorach
    uint8_t num_fats;              // 16:    Liczba tablic FAT (zwykle 2)
    uint16_t max_root_dir_entries; // 17-18: Maksymalna liczba plikĂłw w katalogu gĹĂłwnym (FAT12/16)
    uint16_t total_sectors_16;     // 19-20: Liczba sektorĂłw w systemie plikĂłw (jeĹli 0, patrz bytes 32-35)
    uint8_t media_type;            // 21:    Typ noĹnika (0xF0 - dysk wymienny, 0xF8 - dysk staĹy)
    uint16_t fat1216_size;         // 22-23: Rozmiar kaĹźdej tablicy FAT w sektorach (dla FAT12/16)
    uint16_t sectors_per_track;    // 24-25: Sektory na ĹcieĹźkÄ
    uint16_t num_heads;            // 26-27: Liczba gĹowic w urzÄdzeniu
    uint32_t hidden_sectors;       // 28-31: Liczba sektorĂłw przed startowÄ partycjÄ
    uint32_t total_sectors_32;     // 32-35: Liczba sektorĂłw w systemie plikĂłw (jeĹli bytes 19-20 == 0)

    /* bytes: 36 - 511 */
    uint8_t bios_drive_number;       // 36:    BIOS INT 13h drive number
    uint8_t reserved;                // 37:    Nie uĹźywane
    uint8_t extended_boot_signature; // 38:    Rozszerzony podpis bootujÄcy (0x29)
    uint32_t volume_serial_number;   // 39-42: Numer seryjny woluminu
    char volume_label[11];           // 43-53: Etykieta woluminu w ASCII
    char file_system_type[8];        // 54-61: Typ systemu plikĂłw w ASCII ("FAT12", "FAT16")
    uint8_t not_used[448];           // 62-509: Nie uĹźywane
    uint16_t boot_signature;         // 510-511: Signature value
} __attribute__((packed));

struct volume_t
{
    struct disk_t *disk;
    struct FAT_boot_sector_t boot_sector;
};

struct file_t
{
    struct volume_t *volume;
    struct dir_entry_t *dir_entry;
    uint32_t position;
};

struct disk_t *disk_open_from_file(const char *volume_file_name);
int disk_read(struct disk_t *pdisk, int32_t first_sector, void *buffer, int32_t sectors_to_read);
int disk_close(struct disk_t *pdisk);

struct volume_t *fat_open(struct disk_t *pdisk, uint32_t first_sector);
int fat_close(struct volume_t *pvolume);

struct file_t *file_open(struct volume_t *pvolume, const char *file_name);
int file_close(struct file_t *stream);
size_t file_read(void *ptr, size_t size, size_t nmemb, struct file_t *stream);
int32_t file_seek(struct file_t *stream, int32_t offset, int whence);

struct dir_t
{
    struct volume_t *pvolume;
    int dir_read;
    int files;
};

struct dir_t *dir_open(struct volume_t *pvolume, const char *dir_path);

struct dir_entry_t;

int dir_read(struct dir_t *pdir, struct dir_entry_t *pentry);
int dir_close(struct dir_t *pdir);

#endif // PROJECT1_FILE_READER_H
