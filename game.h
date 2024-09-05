#ifndef GAME_H
#define GAME_H
// Constants: Defines constant values for board size, initial snake length, maximum lives, points per second and per food, and the filename for score storage
#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20
#define INITIAL_SNAKE_LENGTH 3
#define MAX_LIVES 3
#define POINTS_PER_SECOND 1
#define POINTS_PER_FOOD 30
#define SCORE_FILE "snake_scores.txt"
#include <time.h>

// Structure: Defines a position with x and y coordinates
typedef struct
{
    int x, y;
} Position;

// Enum: assigns integer values to directions for better code readability
enum Direction {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};

// Structure: Defines the snake with a body (consisting of positions), a length, and a direction
typedef struct
{
    Position *body;
    int length;
    enum Direction direction;
} Snake;

// Structure: Defines the food with a position

typedef struct
{
    Position position;
} Food;

// Structure: Defines the game with a snake, food, number of lives, score, username, and start time
typedef struct
{
    Snake snake;
    Food food;
    int lives;
    int score;
    char username[50];
    time_t startTime;
} Game;

void initGame(Game *game);      // Start: Declaration of the function to initialize the game
void updateGame(Game *game);    // Update: Declaration of the function to update the game
void resetGame(Game *game);     // Reset: return the snake to its original size, when a life is lost.
void moveSnake(Snake *snake);   // Movement: Declaration of the function to move the snake
int checkCollision(Game *game); // Collision: Declaration of the function to check for collisions
void generateFood(Game *game);  // Food: Declaration of the function to generate food
void endGame(Game *game);       // Life: Declaration of the function to end the game
void saveScore(Game *game);     // History: Declaration of the function to save the score

#endif // GAME_H
