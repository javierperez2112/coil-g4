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

static void delay(int);

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

// Runs the game loop, including I/O
void runGame(Game *game)
{
#ifndef _WINDOWS
    struct termios saved_attributes;
    setInputMode(&saved_attributes);
#endif
    system(CLEAR);
    printf(SNAKE_ASCII_ART);
    if (game->lives == MAX_LIVES)
    {
        printf("Welcome, %s!\n", game->username);
    }
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
        case 'p':
        case 'P':
            system(CLEAR);
            printf(SNAKE_ASCII_ART);
            printf("Game paused, press any key to continue or q to quit.\n");
            printf("Lives: %d  Score: %d\n", game->lives, game->score);
            while (!read(STDIN_FILENO, &key, 1))
                ;
            if (key != 'q' && key != 'Q')
                break; // Pause
        case 'q':
        case 'Q': // Quit
            endGame(game);
            game->lives = 0;
#ifndef _WINDOWS
            resetInputMode(&saved_attributes);
#endif
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
#ifndef _WINDOWS
                resetInputMode(&saved_attributes);
#endif
                return; // Exits the game
            }
            else
            {
#ifndef _WINDOWS
                resetInputMode(&saved_attributes);
#endif
                return;
            }
        }

        updateGame(game); // Update: Updates the game state
        drawGame(game);   // Displays the current game state
        delay(200);       // Delay: Waits for a specified time
    }
}

// Draws the current game board
void drawGame(Game *game)
{
    system(CLEAR);
    printf("User: %s\n", game->username);
    // Draws the game board
    for (int y = -1; y <= BOARD_HEIGHT; y++)
    {
        for (int x = -1; x < BOARD_WIDTH; x++)
        {
            if (y == -1 || y == BOARD_HEIGHT || x == -1)
            {
                printf("X ");
                continue;
            }
            int isBodyPart = 0; // Flag to check if there is a snake body part at this position

            // Checks if there is a part of the snake at this position
            for (int i = 0; i < game->snake.length; i++)
            {
                if (game->snake.body[i].x == x && game->snake.body[i].y == y)
                {
                    // Print head depending on direction
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
                        printf("%s", (i < game->snake.length / 2) ? "0" : "o"); // Make front half bigger
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
                    printf("#"); // Food '#'
                }
                else
                {
                    printf(" "); // Empty space '.'
                }
            }
            printf(" ");
        }
        printf("X\n"); // New line for the game board
    }
    // Displays the number of lives and the current score
    printf("Lives: %d  Score: %d\n", game->lives, game->score);
    printf("Use WASD keys to change directions.\n");
    printf("Press p to pause or q to quit.\n");
}

// Delay: Pauses for the specified number of milliseconds
void delay(int milliseconds)
{
#ifdef _WINDOWS
    Sleep(milliseconds); // Windows-specific function to pause execution for a specified time
#else
    usleep(1000 * milliseconds); // Linux-specific time function
#endif
}
