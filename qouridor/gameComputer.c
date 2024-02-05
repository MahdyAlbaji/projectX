// gameComputer.c

#include "game.h"

extern char **board;

int generateRandomNumber(int low, int high)
{
    return (rand() % (high - low + 1)) + low;
}

void playGameComputer(gameInfo *game, int player)
{
    int moveWall = generateRandomNumber(1, 2); // 1 --> Move , 2 --> Wall

    if (moveWall == 1) // Move
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
        int state = generateRandomNumber(1, 2);
        if (state == 1) model = 'h';
        else model = 'v';

        int x = game->position1[0] - 1;
        int y = game->position1[1] - 1;

        int size = game->size;
        size /= 2;

        if (isValidWall(game, x, y, model))
        {
            getWall(game, x, y, model);
            return;
        }
        else if (isValidWall(game, x, y + 2, model))
        {
            y += 2;
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