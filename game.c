#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

// Start: Initializes the game, including lives, score, snake length, direction, and food position
void initGame(Game *game)
{
    game->lives = MAX_LIVES;      // Sets the number of lives to the maximum value
    generateFood(game);           // Generates the initial position of the food
    game->startTime = time(NULL); // Sets the start time of the game
}

// Reset: return the snake to its original size, when a life is lost.
void resetGame(Game *game)
{
    if (game->snake.body != NULL)
        free(game->snake.body);
    game->snake.length = INITIAL_SNAKE_LENGTH;                                      // Sets the initial snake length
    game->snake.direction = 1;                                                      // Sets the initial direction of the snake
    game->snake.body = (Position *)malloc(INITIAL_SNAKE_LENGTH * sizeof(Position)); // Allocates memory for the snake body
    for (int i = 0; i < INITIAL_SNAKE_LENGTH; i++)
    {
        game->snake.body[i].x = INITIAL_SNAKE_LENGTH - i - 1; // Initializes the x positions of the snake body parts
        game->snake.body[i].y = 0;                            // Sets the y position of the snake body parts to 0
    }
}

// Update: Updates the game state when the snake eats food or time passes
void updateGame(Game *game)
{

    // Checks if the snake has eaten the food
    if (game->snake.body[0].x == game->food.position.x && game->snake.body[0].y == game->food.position.y)
    {
        game->score += POINTS_PER_FOOD;                                                                  // Increases the score
        game->snake.length++;                                                                            // Increases the snake length
        game->snake.body = (Position *)realloc(game->snake.body, game->snake.length * sizeof(Position)); // Allocates additional memory for the new snake body part
        generateFood(game);                                                                              // Generates new food
    }

    time_t currentTime = time(NULL);                                     // Gets the current time
    int elapsedTime = (int)difftime(currentTime, game->startTime);       // Calculates the elapsed time
    game->score += elapsedTime * POINTS_PER_SECOND * game->snake.length; // Increases the score based on the elapsed time
    game->startTime = currentTime;                                       // Updates the start time
}

// Movement: Moves the snake based on its direction
void moveSnake(Snake *snake)
{
    // Shifts the position of the snake body parts
    for (int i = snake->length - 1; i > 0; i--)
    {
        snake->body[i] = snake->body[i - 1];
    }
    // Changes the position of the snake head based on the current direction
    switch (snake->direction)
    {
    case 0:
        snake->body[0].y--;
        break; // Moves up
    case 1:
        snake->body[0].x++;
        break; // Moves right
    case 2:
        snake->body[0].y++;
        break; // Moves down
    case 3:
        snake->body[0].x--;
        break; // Moves left
    }
}

// Collision: Checks if the snake collides with walls or itself
int checkCollision(Game *game)
{
    Snake *snake = &game->snake;
    // Checks for collision with walls
    if (snake->body[0].x < 0 || snake->body[0].x >= BOARD_WIDTH || snake->body[0].y < 0 || snake->body[0].y >= BOARD_HEIGHT)
    {
        return 1;
    }
    // Checks for collision with its own body
    for (int i = 1; i < snake->length; i++)
    {
        if (snake->body[0].x == snake->body[i].x && snake->body[0].y == snake->body[i].y)
        {
            return 1;
        }
    }
    return 0;
}
// Food: Generates new food at a random position
void generateFood(Game *game)
{
    int validPosition = 0;
    while (!validPosition)
    {
        game->food.position.x = rand() % BOARD_WIDTH;  // Random x position
        game->food.position.y = rand() % BOARD_HEIGHT; // Random y position

        validPosition = 1;
        // Checks if the food position does not overlap with any snake body part
        for (int i = 0; i < game->snake.length; i++)
        {
            if (game->snake.body[i].x == game->food.position.x && game->snake.body[i].y == game->food.position.y)
            {
                validPosition = 0;
                break;
            }
        }
        // Checks if the food is not on the edge positions of the board
        if (game->food.position.x == 0 || game->food.position.x == BOARD_WIDTH - 1 || game->food.position.y == 0 || game->food.position.y == BOARD_HEIGHT - 1)
        {
            validPosition = 0;
        }
    }
}
// Life: Ends the game when the snake dies and saves the score
void endGame(Game *game)
{
    saveScore(game);        // Saves the score
    free(game->snake.body); // Frees the memory allocated for the snake body
}

// History: Saves the score and username to a file
void saveScore(Game *game)
{
    FILE *file = fopen(SCORE_FILE, "a"); // Opens the file for appending
    if (file == NULL)
    {
        printf("Error opening the file!\n"); // Error opening the file
        return;
    }
    fprintf(file, "Username: %s, Score: %d\n", game->username, game->score); // Writes the username and score to the file
    fclose(file);                                                            // Closes the file
}
