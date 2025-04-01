//
// Created by jdobr on 23.12.2024.
//

#include "01_file_reader.h"

struct clusters_chain_t *get_chain_fat16(const void * const buffer, size_t size, uint16_t first_cluster){
    if(buffer == NULL || first_cluster == FAT16_CLUSTER_END)
        return NULL;

    struct clusters_chain_t* pclusters = malloc(sizeof(struct clusters_chain_t));
    if(pclusters == NULL)
        return NULL;

    pclusters->size = 1;
    pclusters->clusters = malloc(pclusters->size * sizeof(uint16_t));
    if(pclusters->clusters == NULL) {
        free(pclusters);
        return NULL;
    }
    *(pclusters->clusters) = first_cluster;

    uint16_t *buff = (uint16_t*)buffer, *temp, next_cluster;
    while(pclusters->size < size){
        next_cluster = buff[pclusters->clusters[pclusters->size - 1]];
        if(next_cluster == FAT16_CLUSTER_END)
            break;

        temp = realloc(pclusters->clusters, (pclusters->size+1) * sizeof(uint16_t));
        if(temp == NULL){
            free(pclusters->clusters);
            free(pclusters);
            pclusters = NULL;
            break;
        }
        pclusters->clusters = temp;
        pclusters->clusters[pclusters->size] = next_cluster;
        pclusters->size += 1;
    }

    return pclusters;
}

struct clusters_chain_t *get_chain_fat12(const void * const buffer, size_t size, uint16_t first_cluster){
    if(buffer == NULL || first_cluster == FAT12_CLUSTER_END)
        return NULL;

    struct clusters_chain_t* pclusters = malloc(sizeof(struct clusters_chain_t));
    if(pclusters == NULL)
        return NULL;

    pclusters->size = 1;
    pclusters->clusters = malloc(pclusters->size * sizeof(uint16_t));
    if(pclusters->clusters == NULL) {
        free(pclusters);
        return NULL;
    }
    *(pclusters->clusters) = first_cluster;
    uint8_t *buff = (uint8_t*)buffer;
    uint16_t *temp, next_cluster, cluster;

    while(pclusters->size < size){
        cluster = pclusters->clusters[pclusters->size - 1] * 3 / 2;
        if (pclusters->clusters[pclusters->size - 1] % 2 == 0) {
            next_cluster = ((*(buff + cluster + 1) & 0x0F) << 8 | *(buff + cluster));

        } else {
            next_cluster = (*(buff + cluster + 1) << 8 | *(buff + cluster)) >> 4;
        }

        if(next_cluster == FAT12_CLUSTER_END || next_cluster == 0)
            break;

        temp = realloc(pclusters->clusters, (pclusters->size+1) * sizeof(uint16_t));
        if(temp == NULL){
            free(pclusters->clusters);
            free(pclusters);
            pclusters = NULL;
            return NULL;
        }
        pclusters->clusters = temp;
        pclusters->clusters[pclusters->size] = next_cluster;
        pclusters->size += 1;
    }

    return pclusters;
}

