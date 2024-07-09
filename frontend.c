#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "frontend.h"

// Movement, Food, Growth, Life, Score: Draws the current game board including snake, food, lives, and score

void drawGame(Game *game) {
    system("cls");                                      // Clears the screen


    // Draws the game board
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            int isBodyPart = 0;                         // Flag to check if there is a snake body part at this position

            // Checks if there is a part of the snake at this position
            for (int i = 0; i < game->snake.length; i++) {
                if (game->snake.body[i].x == x && game->snake.body[i].y == y) {
                    printf(i == 0 ? "O" : "o");        // Snake head 'O', body 'o'
                    isBodyPart = 1;
                    break;
                }
            }

            // If there is no snake body part, check if there is food here or an empty space
            if (!isBodyPart) {
                if (game->food.position.x == x && game->food.position.y == y) {
                    printf("F");           // Food 'F'
                } else {
                    printf(".");          // Empty space '.'
                }
            }
        }
        printf("\n");                   // New line for the game board
    }
     // Displays the number of lives and the current score
    printf("Leben: %d  Score: %d\n", game->lives, game->score);
}

// Delay: Pauses for the specified number of milliseconds

void delay(int milliseconds) {
    Sleep(milliseconds);        // Windows-specific function to pause execution for a specified time
}

