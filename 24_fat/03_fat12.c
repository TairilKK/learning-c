#include <stdio.h>
#include "03_file_reader.h"

int main(void) {
    struct disk_t* disk = disk_open_from_file("while_fat12_volume.img");

    char b[12];
    char *buffer = b;
    int count = disk_read(disk, 0, (void *)buffer, 1);
    (void)count;
    disk_close(disk);
    return 0;
}
