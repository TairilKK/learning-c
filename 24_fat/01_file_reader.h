
//
// Created by jdobr on 23.12.2024.
//

#ifndef FAT_PROJECT_MYFAT_H
#define FAT_PROJECT_MYFAT_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>

struct clusters_chain_t
{
    uint16_t *clusters;
    size_t size;
};

#define FAT16_CLUSTER_END 0xFFF8
#define FAT12_CLUSTER_END 0xFF8

struct clusters_chain_t *get_chain_fat16(const void *const buffer, size_t size, uint16_t first_cluster);
struct clusters_chain_t *get_chain_fat12(const void *const buffer, size_t size, uint16_t first_cluster);

#endif // FAT_PROJECT_MYFAT_H
