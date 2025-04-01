//
// Created by jdobr on 09.08.2023.
//
#include <stdio.h>
#include <stdlib.h>

#include "07_board.h"

int create_board(struct board_t **board, int width,int height){
    if(board == NULL || width <= 0 || height <= 0)
        return 1;

    (*board) = ( struct board_t * )calloc(1, sizeof ( struct board_t ));

    if((*board) == NULL)
        return 2;

    (*board)->board = (char **) calloc(height, sizeof(char *));

    if((*board)->board == NULL){
        free_board(*board);
        return 2;
    }
    for(int i = 0; i<height; ++i){
        *((*board)->board + i) = (char *) calloc(width + 1, sizeof(char));
        if(*((*board)->board + i) == NULL) {
            (*board)->height = i;
            free_board(*board);

            return 2;
        }
        for(int j = 0; j<width; ++j)
            *(*((*board)->board + i) + j) = '.';
    }

    (*board)->width = width;
    (*board)->height = height;
    (*board)->is_init = 0;

    (*board)->move_player_up = move_player_up;
    (*board)->move_player_down = move_player_down;
    (*board)->move_player_left = move_player_left;
    (*board)->move_player_right = move_player_right;

    return 0;
}

void free_board(struct board_t *board){
    if(board == NULL)
        return;

    for(int i = 0; i < board->height; i++)
        free(*(board->board + i));
    free(board->board);
    free(board);
}

void display_board(const struct board_t *board){
    if(board == NULL)
        return;

    for(int i = 0; i < board->height; ++i, printf("\n"))
        for(int j = 0; j < board->width; printf("%c", *(*(board->board + i) +j )), ++j);
}

int set_player(struct board_t *board, int x, int y){
    if(board == NULL || board->board == NULL || x<0 || y < 0 || x>=board->width || y>=board->height || board->is_init)
        return 1;

    board->player.x = x;
    board->player.y = y;

    *(*(board->board + y) + x) = '@';

    board->is_init = 1;
    return 0;
}

struct board_t* move_player_up(struct board_t* board){
    if(board == NULL || board->board == NULL || board->height <= 0 || board->width <= 0 || board->is_init == 0 || board->player.x < 0 || board->player.y < 0 || board->player.x >=board->width || board->player.y >=board->height)
        return NULL;

    *(*(board->board + board->player.y) + board->player.x) = '.';

    board->player.y--;
    if(board->player.y < 0)
        board->player.y += board->height;

    *(*(board->board + board->player.y) + board->player.x) = '@';

    return board;
}

struct board_t* move_player_down(struct board_t* board){
    if(board == NULL || board->board == NULL || board->height <= 0 || board->width <= 0 || board->is_init == 0 || board->player.x < 0 || board->player.y < 0 || board->player.x >=board->width || board->player.y >=board->height)
        return NULL;

    *(*(board->board + board->player.y) + board->player.x) = '.';

    board->player.y++;
    if(board->player.y >= board->height)
        board->player.y -= board->height;

    *(*(board->board + board->player.y) + board->player.x) = '@';

    return board;
}

struct board_t* move_player_left(struct board_t* board){
    if(board == NULL || board->board == NULL || board->height <= 0 || board->width <= 0 || board->is_init == 0 || board->player.x < 0 || board->player.y < 0 || board->player.x >=board->width || board->player.y >=board->height)
        return NULL;

    *(*(board->board + board->player.y) + board->player.x) = '.';

    board->player.x--;
    if(board->player.x < 0)
        board->player.x += board->width;

    *(*(board->board + board->player.y) + board->player.x) = '@';

    return board;
}

struct board_t* move_player_right(struct board_t* board){
    if(board == NULL || board->board == NULL || board->height <= 0 || board->width <= 0 || board->is_init == 0 || board->player.x < 0 || board->player.y < 0 || board->player.x >=board->width || board->player.y >=board->height)
        return NULL;

    *(*(board->board + board->player.y) + board->player.x) = '.';

    board->player.x++;
    if(board->player.x >= board->width)
        board->player.x -= board->width;

    *(*(board->board + board->player.y) + board->player.x) = '@';

    return board;
}
