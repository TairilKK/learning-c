#include <stdio.h>

int longest_series(unsigned int x);

int main() {
    unsigned int a;

    printf("Podaj liczbę: ");
    if(scanf("%u", &a)!=1){
        printf("Incorrect input");
        return 1;
    }

    printf("Wynik: %d", longest_series(a));

    return 0;
}


int longest_series(unsigned int x) {
    int act = 0, max = 0;
    for (int i = 0; i < (int) sizeof(unsigned int) * 8; ++i) {
        if (x & (1 << i)) {
            act++;
        } else {
            if (act > max) {
                max = act;
            }
            act = 0;
        }
    }
    if (act > max) {
        max = act;
    }
    return max;
}