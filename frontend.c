#include <stdio.h>
#include "frontend.h"
#ifdef _WINDOWS
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#endif

#ifdef _WINDOWS
#define CLEAR "cls" // Clear command in Windows
#else
#define CLEAR "clear" // Clear command in Linux
#endif

void delay(int);

#ifndef _WINDOWS // Linux-specific POSIX functions
void setInputMode(struct termios *saved_attributes)
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
void resetInputMode(struct termios *saved_attributes)
{
    tcsetattr(STDIN_FILENO, TCSANOW, saved_attributes);
}
#endif

// Movement, Food, Growth, Life, Score: Draws the current game board including snake, food, lives, and score
// TO DO: include Windows version (_WINDOWS)
void runGame(Game *game)
{
#ifndef _WINDOWS
    struct termios saved_attributes;
    setInputMode(&saved_attributes);
#endif
    system(CLEAR);
    printf("Lives: %d\n", game->lives);
    printf("Press any key to start or q to quit...\n");
    char key;
#ifndef _WINDOWS
    while (!read(STDIN_FILENO, &key, 1))
        ;
#else
    while (1)
    {
        if (_kbhit())
        {
            key = _getch();
            break;
        }
    }
#endif
    if (key == 'q' || key == 'Q')
    {
        printf("Game Over! Score: %d\n", game->score);
    }
    // Main game loop
    while (1)
    {
// Keyboard: Checks if a key has been pressed
#ifdef _WINDOWS
        if (_kbhit())
        {
            key = _getch();
        }
#else
        read(STDIN_FILENO, &key, 1);
#endif
        switch (key)
        {
        case 'w':
        case 'W':
            if (game->snake.direction != DOWN)
                game->snake.direction = UP;
            break; // Up
        case 'd':
        case 'D':
            if (game->snake.direction != LEFT)
                game->snake.direction = RIGHT;
            break; // Right
        case 's':
        case 'S':
            if (game->snake.direction != UP)
                game->snake.direction = DOWN;
            break; // Down
        case 'a':
        case 'A':
            if (game->snake.direction != RIGHT)
                game->snake.direction = LEFT;
            break; // Left
        case 'q':
        case 'Q':
            endGame(game);
            game->lives = 0;
            resetInputMode(&saved_attributes);
            return; // Quit
        default:
            break;
        }

        moveSnake(&game->snake); // Movement: Moves the snake
        if (checkCollision(game))
        { // Collision: Checks for collisions
            game->lives--;
            if (game->lives == 0)
            {                                                  // Life: Checks if there are no lives left
                printf("Game Over! Score: %d\n", game->score); // Displays the final score
                endGame(game);                                 // Ends the game
                resetInputMode(&saved_attributes);
                return; // Exits the game
            }
            else
            {
                resetInputMode(&saved_attributes);
                return;
            }
        }

        updateGame(game); // Update: Updates the game state
        drawGame(game);   // Displays the current game state
        delay(200);       // Delay: Waits for a specified time
    }
}

void drawGame(Game *game)
{
    system(CLEAR);
    // Draws the game board
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            int isBodyPart = 0; // Flag to check if there is a snake body part at this position

            // Checks if there is a part of the snake at this position
            for (int i = 0; i < game->snake.length; i++)
            {
                if (game->snake.body[i].x == x && game->snake.body[i].y == y)
                {
                    // Print head depending on direction, or body segment.
                    if (i == 0)
                    {
                        switch (game->snake.direction)
                        {
                        case UP:
                            printf("ʌ");
                            break;
                        case RIGHT:
                            printf(">");
                            break;
                        case DOWN:
                            printf("v");
                            break;
                        case LEFT:
                            printf("<");
                            break;
                        }
                    }
                    else
                    {
                        printf("o");
                    }
                    isBodyPart = 1;
                    break;
                }
            }

            // If there is no snake body part, check if there is food here or an empty space
            if (!isBodyPart)
            {
                if (game->food.position.x == x && game->food.position.y == y)
                {
                    printf("#"); // Food 'F'
                }
                else
                {
                    printf("."); // Empty space '.'
                }
            }
        }
        printf("\n"); // New line for the game board
    }
    // Displays the number of lives and the current score
    printf("Lives: %d  Score: %d\n", game->lives, game->score);
}

// Delay: Pauses for the specified number of milliseconds

void delay(int milliseconds)
{
#ifdef _WINDOWS
    Sleep(milliseconds); // Windows-specific function to pause execution for a specified time
#else
    usleep(1000 * milliseconds);
#endif
}
