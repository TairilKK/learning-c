//
// Created by jdobr on 27.08.2023.
//

#include <stdio.h>
#include <stdlib.h>

#include "05_maze.h"

int load_maze(const char *filename, char ***labirynth){
    if(!filename || !labirynth) return 1;

    /* Sprawdzanie pliku */
    FILE *f = fopen(filename, "r");
    if(!f) return 2;

    /* Sprawdzanie poprawnosci pliku */
    char c;
    int w = 0, h = 0, size_check = 0;
    int flag = 0;
    if((c = fgetc(f)) == EOF){ fclose(f); return 3; }
    fseek(f, -1, SEEK_CUR);
    while((c = fgetc(f)) != EOF) {
        if(!(c == '#' || c ==' ' || c=='a' || c=='b' || c=='\n')) { fclose(f); return 3; }
        if(flag == 0 && c != '\n')
            w++;

        if(c != '\n')
            size_check++;
        else {
            flag = 1;
            if(size_check != w) {
                fclose(f);
                return 3;
            }
            size_check = 0;
            h++;
        }
    }
    h++;

    /* Alokacja pamieci */
    *labirynth = (char **)calloc(h + 1, sizeof(char *));
    if(!*labirynth){ fclose(f); return 4; }

    for(int i = 0; i < h; ++i){
        *((*labirynth) + i) = calloc(w + 1, sizeof(char));
        if(!*((*labirynth) + i)) { free_maze(*labirynth); fclose(f);return 4; }
    }

    /* Przypisywanie labiryntu do zmiennej na labirynt */
    fseek(f, 0, SEEK_SET);
    int i = 0, j = 0;
    while((c = fgetc(f)) != EOF && j < h && i <= w){
        if(c!='\n' && i < w) {
            *(*((*labirynth) + j) + i) = c;
            ++i;
        }else {
            i = 0;
            j++;
        }
    }
    *(*labirynth + h) = NULL;

    fclose(f);
    return 0;
}
int getWidthHeight(char **maze, int *w, int *h){
    if(!maze || !w || !h) return 1;
    for(*h = 0; *(maze + *h); (*h)++);
    int ch = 0;
    for(ch = 0; *(maze + ch); ch++);
    if(ch != *h) return -1;

    for(*w = 0; *(*(maze) + *w) != '\0'; (*w)++);
    int cw = 0;
    for(cw = 0; *(*(maze + 1) + cw) != '\0'; cw++);
    if(cw != *w)
        return -1;
    return 0;
}

int solve_maze(char **maze, int x, int y){
    if(!maze) return -1;

    int w, h;
    int ret = getWidthHeight(maze, &w, &h);
    if(x >= w || y >= h || x < 0 || y < 0 || ret != 0) return -1;

    char c;
    for(int i = 0; i < h; i++) {
        for (int j = 0; j < w; ++j) {
            c = *(*(maze + i) + j);
            if (!(c == '#' || c == ' ' || c == 'a' || c == 'b' || c == '*')) {
                return -1;
            }
        }
    }


    if(*(*(maze + y) + x) == 'b') return 1;
    if(*(*(maze + y) + x) == '#') return -1;
    if (*(*(maze + y) + x) == '*') return 0;
    if(*(*(maze + y) + x) != 'a') *(*(maze + y) + x) = '*';


    if (solve_maze(maze, x + 1, y) == 1) return 1;
    if (solve_maze(maze, x - 1, y) == 1) return 1;
    if (solve_maze(maze, x, y + 1) == 1) return 1;
    if (solve_maze(maze, x, y - 1) == 1) return 1;

    if(*(*(maze + y) + x) != 'a') *(*(maze + y) + x) = ' ';
    return 0;
}

void free_maze(char **maze){
    if(!maze) return;
    int i = 0;
    while(*(maze + i)) {
        free(*(maze + i));
        ++i;
    }
    free(*(maze + i));
    free(maze);
    maze = NULL;
}
