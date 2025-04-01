//
// Created by jdobr on 27.08.2023.
//

#ifndef INC_12_MAZE_H
#define INC_12_MAZE_H

int load_maze(const char *filename, char ***labirynth);
int solve_maze(char **maze, int x, int y);
void free_maze(char **maze);

#endif //INC_12_MAZE_H
