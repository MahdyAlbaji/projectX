// gameComputer.c

#include "game.h"

extern char **board;

int generateRandomNumber(int low, int high)
{
    srand(time(NULL));
    
    int lower = low;
    int upper = high;

    int x = (rand() % (upper - lower + 1)) + lower;
    
    return x;
}

void playGameComputer(gameInfo *game, int player)
{
    int move_or_wall = generateRandomNumber(1, 2); // 1 --> move , 2 --> wall

    if (move_or_wall == 1) // move
    {
        int direction = 3;

        if (isValidMove(game, direction, player))
        {
            getMove(game, direction, player);
            return;
        }
        
        while (!isValidMove(game, direction, player))
        {
            direction = generateRandomNumber(1, 4);
            if (isValidMove(game, direction, player)) getMove(game, direction, player);
        }

    }
    else // wall
    {
        char model;
        int state = generateRandomNumber(1, 10);
        if (state % 2 == 0) model = 'h';
        else model = 'v';

        int x = game->position1[0] - 1;
        int y = game->position1[1];

        int size = game->size;
        size /= 2;

        if (isValidWall(game, x, y, model))
        {
            getWall(game, x, y, model);
            return;
        }
        
        while (!isValidWall(game, x, y, model))
        {
            x = generateRandomNumber(1, size);
            y = generateRandomNumber(1, size);

            if (isValidWall(game, x, y, model)) getWall(game, x, y, model);
        }
    }
}