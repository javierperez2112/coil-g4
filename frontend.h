#ifndef FRONTEND_H
#define FRONTEND_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)
#define _WINDOWS         // If on Windows define _WINDOWS macro.
#elif defined(__linux__) // If on GNU/Linux do nothing
#else
#error "Unknown operating system!"
#endif

#include "game.h"

void runGame(Game *game);  // Run the game loop, exit when game over.
void drawGame(Game *game); // Function to draw the current game state.


#endif
