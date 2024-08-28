#ifndef FRONTEND_H
#define FRONTEND_H

#include "game.h"

void runGame(Game *game);  // Run the game loop, exit when game over.
void drawGame(Game *game); // Function to draw the current game state.

#endif
