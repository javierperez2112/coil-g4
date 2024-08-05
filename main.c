#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <conio.h>
#include <time.h>
#include <ncurses.h>
#include "game.h"
#include "frontend.h"
#include <termios.h>

void set_input_mode(struct termios *saved_attributes)
{
    struct termios tattr;

    // Save the terminal attributes so we can restore them later
    tcgetattr(STDIN_FILENO, saved_attributes);

    // Set the terminal to raw mode
    tcgetattr(STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tattr.c_cc[VMIN] = 0;              // Minimum number of characters for noncanonical read
    tattr.c_cc[VTIME] = 1;             // Timeout for noncanonical read

    tcsetattr(STDIN_FILENO, TCSANOW, &tattr);
}

// Function to restore terminal attributes
void reset_input_mode(struct termios *saved_attributes)
{
    tcsetattr(STDIN_FILENO, TCSANOW, saved_attributes);
}

int main()
{
    Game game; // Structure: Declares the game state

    // Username: Prompts the user to enter their username
    printf("Enter your username: ");
    scanf("%49s", game.username); // Reads the username input
    struct termios saved_attributes;
    set_input_mode(&saved_attributes);

    initGame(&game); // Start: Initializes the game

    // Main game loop
    while (1)
    {
        // Keyboard: Checks if a key has been pressed
        char key;
        read(STDIN_FILENO, &key, 1);
        switch (key)
        {
        case 'w':
            if (game.snake.direction != 2)
                game.snake.direction = 0;
            break; // Up
        case 'd':
            if (game.snake.direction != 3)
                game.snake.direction = 1;
            break; // Right
        case 's':
            if (game.snake.direction != 0)
                game.snake.direction = 2;
            break; // Down
        case 'a':
            if (game.snake.direction != 1)
                game.snake.direction = 3;
            break; // Left
        case 'q':
            endGame(&game);
            reset_input_mode(&saved_attributes);
            return 0; // Quit
        default:
            break;
        }

        moveSnake(&game.snake); // Movement: Moves the snake
        if (checkCollision(&game))
        {                 // Collision: Checks for collisions
            game.lives--; // Decrements the number of lives
            if (game.lives == 0)
            {                                                 // Life: Checks if there are no lives left
                printf("Game Over! Score: %d\n", game.score); // Displays the final score
                endGame(&game);                               // Ends the game
                return 0;                                     // Exits the game
            }
        }

        updateGame(&game); // Update: Updates the game state
        drawGame(&game);   // Displays the current game state
        delay(200);        // Delay: Waits for a specified time
    }

    return 0; // Program end
}
