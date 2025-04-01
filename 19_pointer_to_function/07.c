#include <stdio.h>

#include "board.h"

int main() {
    struct board_t * board;
    int width, height, x ,y;
    int res;
    char input = 's';

    printf("Enter width and height of the board: ");
    if(scanf("%d %d", &width, &height) != 2){
        printf("Incorrect input");
        return 1;
    }

    res = create_board(&board, width, height);
    if(res == 2){
        printf("Failed to allocate memory");
        return 8;
    }
    else if(res == 1){
        printf("Incorrect input data");
        return 2;
    }

    printf("Enter player's initial coordinates (x, y):");
    if(scanf("%d %d", &x, &y) != 2){
        printf("Incorrect input");
        free_board(board);
        return 1;
    }
    while(getchar()!= '\n');

    res = set_player(board, x, y);
    if(res != 0){
        printf("Incorrect input data");
        free_board(board);
        return 2;
    }

    display_board(board);

    while(1){
        printf("Choose your action: ");

        scanf("%c", &input);
        while(getchar()!= '\n');

        if(input == 'w') {
            board = board->move_player_up(board);
            display_board(board);
        }
        else if(input == 'a') {
            board = board->move_player_left(board);
            display_board(board);
        }
        else if(input == 's') {
            board = board->move_player_down(board);
            display_board(board);
        }
        else if(input == 'd') {
            board = board->move_player_right(board);
            display_board(board);
        }
        else if(input == 'q'){
            free_board(board);
            return 0;
        }
        else
            printf("Incorrect choice\n");

    }
}
