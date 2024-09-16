#ifndef FRONTEND_H
#define FRONTEND_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)
#define _WINDOWS         // If on Windows define _WINDOWS macro.
#define CLEAR "cls" // Clear command in Windows
#elif defined(__linux__) // If on GNU/Linux do nothing
#define CLEAR "clear" // Clear command in Linux
#else
#error "Unknown operating system!"
#endif

#include "game.h"

// Title ASCII art for title and pause screen.
#define SNAKE_ASCII_ART ("\n███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗\n██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝\n███████╗██╔██╗ ██║███████║█████╔╝ █████╗ \n╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝  \n███████║██║ ╚████║██║  ██║██║  ██╗███████╗\n╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝\n")

void runGame(Game *game);  // Run the game loop, exit when game over.
void drawGame(Game *game); // Function to draw the current game state.


#endif
