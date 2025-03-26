#include <stdio.h>

#include "12_message_t.h"


int main() {
    char filename[31];
    printf("Podaj nazwÄ pliku: ");
    scanf("%30[^\n]s", filename);

    struct message_t data[100];
    int result = load_data(data, 100, filename);

    if (result == -2) {
        printf("Couldn't open file\n");
        return 4;
    } else if (result < 0) {
        printf("File corrupted\n");
        return 6;
    }

    char buffer[1101];
    decode_message(data, result, buffer, sizeof(buffer));
    printf("%s", buffer);
    return 0;
}


