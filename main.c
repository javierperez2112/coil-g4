#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef _WINDOWS
#include <conio.h>
#else
#include <termios.h>
#endif
#include <time.h>
#include "game.h"
#include "frontend.h"

int main()
{
    Game game; // Structure: Declares the game state
    int lives = MAX_LIVES;
    game.score = 0;
    printf("Enter your username: ");
    scanf("%49s", game.username); // Reads the username input
    do
    {
        initGame(&game, lives);
        runGame(&game);
        lives--;
    } while (game.lives > 0);
    return 0;
}