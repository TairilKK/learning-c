//
// Created by jdobr on 23.12.2024.
//

#ifndef FAT_PROJECT_MYFAT_H
#define FAT_PROJECT_MYFAT_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>

struct dir_entry_t{
    char name[12];
    size_t size;
    uint8_t is_archived : 1;
    uint8_t is_readonly : 1;
    uint8_t is_system : 1;
    uint8_t is_hidden : 1;
    uint8_t is_directory : 1;
    struct {
        uint8_t day;
        uint8_t month;
        uint16_t year;
    } creation_date;
    struct {
        uint8_t second;
        uint8_t minute;
        uint8_t hour;
    } creation_time;
};

struct root_directory_structure{
    char file_name[11];             // 0 - 10
    uint8_t attributes;             // 11
    uint8_t reserved;               // 12
    uint8_t creation_time_ts;       // 13
    uint16_t creation_time_hms;     // 14-15
    uint16_t creation_date;         // 16-17
    uint16_t access_date;           // 18-19
    uint16_t high_order_first_cluster; // 20-21
    uint16_t modified_time;         // 22-23
    uint16_t modified_date;         // 24-25
    uint16_t low_order_first_cluster; // 26-27
    uint32_t file_size;             // 28-31
} __attribute__ ((__packed__));

struct dir_entry_t *read_directory_entry(const char *filename);

#endif //FAT_PROJECT_MYFAT_H
