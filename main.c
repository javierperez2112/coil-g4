#include <stdio.h>
//#include <conio.h>
#include "game.h"
#include "frontend.h"

int main() {
    Game game;      // Structure: Declares the game state

    // Username: Prompts the user to enter their username
    printf("Enter your username: ");
    scanf("%49s", game.username);       // Reads the username input


    initGame(&game);        // Start: Initializes the game

     // Main game loop
    while (1) {
             // Keyboard: Checks if a key has been pressed
        if (_kbhit()) {
            char key = _getch();        // Gets the pressed key
            switch (key) {
                case 'w': if (game.snake.direction != 2) game.snake.direction = 0; break;   //Up
                case 'd': if (game.snake.direction != 3) game.snake.direction = 1; break;   //Right
                case 's': if (game.snake.direction != 0) game.snake.direction = 2; break;   //Down
                case 'a': if (game.snake.direction != 1) game.snake.direction = 3; break;   //Left
                case 'q': endGame(&game); return 0;     // Quit
            }
        }

        moveSnake(&game.snake);     // Movement: Moves the snake
        if (checkCollision(&game)) {        // Collision: Checks for collisions
            game.lives--;                   // Decrements the number of lives
            if (game.lives == 0) {          // Life: Checks if there are no lives left
                printf("Game Over! Score: %d\n", game.score);   // Displays the final score
                endGame(&game);                 // Ends the game
                return 0;                       // Exits the game
            }
        }

        updateGame(&game);      // Update: Updates the game state
        drawGame(&game);        // Displays the current game state
        delay(200);             // Delay: Waits for a specified time

    }

    return 0;           // Program end

}
