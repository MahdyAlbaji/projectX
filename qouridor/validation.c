// validation.c

#include "game.h"

extern char **board;


int isValidMove(gameInfo *game, int direction, int player)
{
    int size = game->size;

    if (player == 1)
    {
        int x = game->position1[0];
        int y = game->position1[1];
        if (direction == 1 && x - 2 < size && x - 2 >= 0 && board[x - 1][y] != '=' && board[x - 2][y] == ' ' && direction >= 1 && direction <= 4) return 1;
        else if (direction == 2 && y + 2 < size && y + 2 >= 0 && board[x][y + 1] != '|' && board[x][y + 2] == ' ' && direction >= 1 && direction <= 4) return 1;
        else if (direction == 3 && x + 2 < size && x + 2 >= 0 && board[x + 1][y] != '=' && board[x + 2][y] == ' ' && direction >= 1 && direction <= 4) return 1;
        else if (direction == 4 && y - 2 < size && y - 2 >=0 && board[x][y - 1] != '|' && board[x][y - 2] == ' ' && direction >= 1 && direction <= 4) return 1;
    }
    else
    {
        int x = game->position2[0];
        int y = game->position2[1];
        if (direction == 1 && x - 2 < size && x - 2 >= 0 && board[x - 1][y] != '=' && board[x - 2][y] == ' ' && direction >= 1 && direction <= 4) return 1;
        else if (direction == 2 && y + 2 < size && y + 2 >= 0 && board[x][y + 1] != '|' && board[x][y + 2] == ' ' && direction >= 1 && direction <= 4) return 1;
        else if (direction == 3 && x + 2 < size && x + 2 >= 0 && board[x + 1][y] != '=' && board[x + 2][y] == ' ' && direction >= 1 && direction <= 4) return 1;
        else if (direction == 4 && y - 2 < size && y - 2 >=0 && board[x][y - 1] != '|' && board[x][y - 2] == ' ' && direction >= 1 && direction <= 4) return 1;
    }
    return 0;
}

int pseudoDFS(gameInfo *game, int player)
{
    int size = game->size;
    int player1State = 0;
    int player2State = 0;

    if (player == 2)
    {
        int x = game->position1[0];
        int y = game->position1[1];

        if (x == 0 && y == 0)
        {
            player1State += 2;
            if (board[x][y + 1] == '|') player1State++;
            if (board[x + 1][y] == '=') player1State++;
        }
        else if (x == 0 && y == size - 1)
        {
            player1State += 2;
            if (board[x][y - 1] == '|') player1State++;
            if (board[x + 1][y] == '=') player1State++;
        }
        else if (x == size - 1 && y == 0)
        {
            player1State += 2;
            if (board[x - 1][y] == '=') player1State++;
            if (board[x][y + 1] == '|') player1State++;
        }
        else if (x == size - 1 && y == size - 1)
        {
            player1State += 2;
            if (board[x - 1][y] == '=') player1State++;
            if (board[x][y - 1] == '|') player1State++;
        }
        else if (x == 0)
        {
            player1State++;
            if (board[x + 1][y] == '=') player1State++;
            if (board[x][y + 1] == '|') player1State++;
            if (board[x][y - 1] == '|') player1State++;
        }
        else if (x == size - 1)
        {
            player1State++;
            if (board[x - 1][y] == '=') player1State++;
            if (board[x][y - 1] == '|') player1State++;
            if (board[x][y + 1] == '|') player1State++;
        }
        else if (y == 0)
        {
            player1State++;
            if (board[x][y + 1] == '|') player1State++;
            if (board[x + 1][y] == '=') player1State++;
            if (board[x - 1][y] == '=') player1State++;
        }
        else if (y == size - 1)
        {
            player1State++;
            if (board[x][y - 1] == '|') player1State++;
            if (board[x + 1][y] == '=') player1State++;
            if (board[x - 1][y] == '=') player1State++;
        }
        else
        {
            if (board[x + 1][y] == '=') player1State++;
            if (board[x - 1][y] == '=') player1State++;
            if (board[x][y + 1] == '|') player1State++;
            if (board[x][y - 1] == '|') player1State++;
        }

        if (player1State < 3) return 1;
        else return 0;
    }
    else
    {
        int x = game->position2[0];
        int y = game->position2[1];

        if (x == 0 && y == 0)
        {
            player2State += 2;
            if (board[x][y + 1] == '|') player2State++;
            if (board[x + 1][y] == '=') player2State++;
        }
        else if (x == 0 && y == size - 1)
        {
            player2State += 2;
            if (board[x][y - 1] == '|') player2State++;
            if (board[x + 1][y] == '=') player2State++;
        }
        else if (x == size - 1 && y == 0)
        {
            player2State += 2;
            if (board[x - 1][y] == '=') player2State++;
            if (board[x][y + 1] == '|') player2State++;
        }
        else if (x == size - 1 && y == size - 1)
        {
            player2State += 2;
            if (board[x - 1][y] == '=') player2State++;
            if (board[x][y - 1] == '|') player2State++;
        }
        else if (x == 0)
        {
            player2State++;
            if (board[x + 1][y] == '=') player2State++;
            if (board[x][y + 1] == '|') player2State++;
            if (board[x][y - 1] == '|') player2State++;
        }
        else if (x == size - 1)
        {
            player2State++;
            if (board[x - 1][y] == '=') player2State++;
            if (board[x][y - 1] == '|') player2State++;
            if (board[x][y + 1] == '|') player2State++;
        }
        else if (y == 0)
        {
            player2State++;
            if (board[x][y + 1] == '|') player2State++;
            if (board[x + 1][y] == '=') player2State++;
            if (board[x - 1][y] == '=') player2State++;
        }
        else if (y == size - 1)
        {
            player2State++;
            if (board[x][y - 1] == '|') player2State++;
            if (board[x + 1][y] == '=') player2State++;
            if (board[x - 1][y] == '=') player2State++;
        }
        else
        {
            if (board[x + 1][y] == '=') player2State++;
            if (board[x - 1][y] == '=') player2State++;
            if (board[x][y + 1] == '|') player2State++;
            if (board[x][y - 1] == '|') player2State++;
        }

        if (player2State < 3) return 1;
        else return 0;
    }

}

int isValidWall(gameInfo *game, int x, int y, char model)
{
    if (model == 'v')
    {
        return (board[x - 1][y] == ':' && board[x + 1][y] == ':' && x < (2 * game->size) && x > 0 && y < (2 * game->size) && y > 0);
    }
    else if (model == 'h')
    {
        return (board[x][y - 1] == '-' && board[x][y + 1] == '-' && x < (2 * game->size) && x > 0 && y < (2 * game->size) && y > 0);
    }
    return 0;
}
