//
// Created by jdobr on 23.12.2024.
//

#ifndef FAT_PROJECT_MYFAT_H
#define FAT_PROJECT_MYFAT_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>

#define NAME_SEPARATOR ' '
#define IS_BIT_SET(value, bit) (((value) & (1 << (bit))) ? 1 : 0)
#define IS_ALPHA(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
#define IS_ALPHA_SPACE(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')

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
    uint16_t high_order_first_cluster;
    uint16_t low_order_first_cluster;
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

struct clusters_chain_t {
    uint16_t *clusters;
    size_t size;
};

#define FAT16_CLUSTER_END 0xFFF8
#define FAT12_CLUSTER_END 0xFF8

struct clusters_chain_t *get_chain_fat16(const void * const buffer, size_t size, uint16_t first_cluster);
struct clusters_chain_t *get_chain_fat12(const void * const buffer, size_t size, uint16_t first_cluster);

struct dir_entry_t *read_directory_entry(const char *filename);

#endif //FAT_PROJECT_MYFAT_H
