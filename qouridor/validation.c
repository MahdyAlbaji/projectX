// validation.c

#include "game.h"

extern char **board;


int isValidMove(gameInfo *game, int direction, int player)
{
    int size = game->size;
    char sign1 = game->player1Sign;
    char sign2 = game->player2Sign;

    if (player == 1)
    {
        int x = game->position1[0];
        int y = game->position1[1];
        if (direction == 1 && x - 2 < size && x - 2 >= 0 && board[x - 2][y] != sign2 && board[x - 1][y] != '=' && direction >= 1 && direction <= 4) return 1;
        else if (direction == 2 && y + 2 < size && y + 2 >= 0 && board[x][y + 2] != sign2 && board[x][y + 1] != '|' && direction >= 1 && direction <= 4) return 1;
        else if (direction == 3 && x + 2 < size && x + 2 >= 0 && board[x + 2][y] != sign2 && board[x + 1][y] != '=' && direction >= 1 && direction <= 4) return 1;
        else if (direction == 4 && y - 2 < size && y - 2 >=0 && board[x][y - 2] != sign2 && board[x][y - 1] != '|' && direction >= 1 && direction <= 4) return 1;
    }
    else
    {
        int x = game->position2[0];
        int y = game->position2[1];
        if (direction == 1 && x - 2 < size && x - 2 >= 0 && board[x - 2][y] != sign1 && board[x - 1][y] != '=' && direction >= 1 && direction <= 4) return 1;
        else if (direction == 2 && y + 2 < size && y + 2 >= 0 && board[x][y + 2] != sign1 && board[x][y + 1] != '|' && direction >= 1 && direction <= 4) return 1;
        else if (direction == 3 && x + 2 < size && x + 2 >= 0 && board[x + 2][y] != sign1 && board[x + 1][y] != '=' && direction >= 1 && direction <= 4) return 1;
        else if (direction == 4 && y - 2 < size && y - 2 >=0 && board[x][y - 2] != sign1 && board[x][y - 1] != '|' && direction >= 1 && direction <= 4) return 1;
    }
    return 0;
}

int isValidWall(gameInfo *game, int x, int y, char model)
{
    if (model == 'v')
    {
        if (board[x][y + 1] != '=' || board[x][y - 1] != '=')
        {
            return (board[x - 1][y] == ':' && board[x + 1][y] == ':' && x < (2 * game->size) && x > 0 && y < (2 * game->size) && y > 0);
        }
    }
    else if (model == 'h')
    {
        if (board[x - 1][y] != '|' || board[x + 1][y] != '|')
        {
            return (board[x][y - 1] == '-' && board[x][y + 1] == '-' && x < (2 * game->size) && x > 0 && y < (2 * game->size) && y > 0);
        }
    }
    return 0;
}

int pseudoDFS(gameInfo *game, int x, int y, char model, int player)
{
    int size = game->size;
    int player1State = 0;
    int player2State = 0;

    if (model == 'h') 
    {
        //if (board[x + 1][y] != '|' && board[x + 1][y] != '|')
        
            board[x][y + 1] = '=';
            board[x][y - 1] = '=';
        
       
    }
    else
    {
       // if (board[x][y + 1] != '=' && board[x][y - 1])
        
            board[x + 1][y] = '|';
            board[x - 1][y] = '|';
        
        
    }

    int x1 = game->position1[0];
    int y1 = game->position1[1];

    if (x1 == 0 && y1 == 0)
    {
        player1State += 2;
        if (board[x1][y1 + 1] == '|') player1State++;
        if (board[x1 + 1][y1] == '=') player1State++;
    }
    else if (x1 == 0 && y1 == size - 1)
    {
        player1State += 2;
        if (board[x1][y1 - 1] == '|') player1State++;
        if (board[x1 + 1][y1] == '=') player1State++;
    }
    else if (x1 == size - 1 && y1 == 0)
    {
        player1State += 2;
        if (board[x1 - 1][y1] == '=') player1State++;
        if (board[x1][y1 + 1] == '|') player1State++;
    }
    else if (x1 == size - 1 && y1 == size - 1)
    {
        player1State += 2;
        if (board[x1 - 1][y1] == '=') player1State++;
        if (board[x1][y1 - 1] == '|') player1State++;
    }
    else if (x1 == 0)
    {
        player1State++;
        if (board[x1 + 1][y1] == '=') player1State++;
        if (board[x1][y1 + 1] == '|') player1State++;
        if (board[x1][y1 - 1] == '|') player1State++;
    }
    else if (x1 == size - 1)
    {
        player1State++;
        if (board[x1 - 1][y1] == '=') player1State++;
        if (board[x1][y1 - 1] == '|') player1State++;
        if (board[x1][y1 + 1] == '|') player1State++;
    }
    else if (y1 == 0)
    {
        player1State++;
        if (board[x1][y1 + 1] == '|') player1State++;
        if (board[x1 + 1][y1] == '=') player1State++;
        if (board[x1 - 1][y1] == '=') player1State++;
    }
    else if (y1 == size - 1)
    {
        player1State++;
        if (board[x1][y1 - 1] == '|') player1State++;
        if (board[x1 + 1][y1] == '=') player1State++;
        if (board[x1 - 1][y1] == '=') player1State++;
    }
    else
    {
        if (board[x1 + 1][y1] == '=') player1State++;
        if (board[x1 - 1][y1] == '=') player1State++;
        if (board[x1][y1 + 1] == '|') player1State++;
        if (board[x1][y1 - 1] == '|') player1State++;
    }

    if (model == 'h') 
    {
        board[x][y + 1] = ' ';
        board[x][y - 1] = ' ';
    }
    else
    {
        board[x + 1][y] = ' ';
        board[x - 1][y] = ' ';
    }

    if (player1State < 4) return 1;
    else return 0;


    int x2 = game->position2[0];
    int y2= game->position2[1];

    if (x2 == 0 && y2 == 0)
    {
        player2State += 2;
        if (board[x2][y2+ 1] == '|') player2State++;
        if (board[x2 + 1][y2] == '=') player2State++;
    }
    else if (x2 == 0 && y2 == size - 1)
    {
        player2State += 2;
        if (board[x2][y2- 1] == '|') player2State++;
        if (board[x2 + 1][y2] == '=') player2State++;
    }
    else if (x2 == size - 1 && y2 == 0)
    {
        player2State += 2;
        if (board[x2 - 1][y2] == '=') player2State++;
        if (board[x2][y2+ 1] == '|') player2State++;
    }
    else if (x2 == size - 1 && y2 == size - 1)
    {
        player2State += 2;
        if (board[x2 - 1][y2] == '=') player2State++;
        if (board[x2][y2- 1] == '|') player2State++;
    }
    else if (x2 == 0)
    {
        player2State++;
        if (board[x2 + 1][y2] == '=') player2State++;
        if (board[x2][y2+ 1] == '|') player2State++;
        if (board[x2][y2- 1] == '|') player2State++;
    }
    else if (x2 == size - 1)
    {
        player2State++;
        if (board[x2 - 1][y2] == '=') player2State++;
        if (board[x2][y2- 1] == '|') player2State++;
        if (board[x2][y2+ 1] == '|') player2State++;
    }
    else if (y2 == 0)
    {
        player2State++;
        if (board[x2][y2+ 1] == '|') player2State++;
        if (board[x2 + 1][y2] == '=') player2State++;
        if (board[x2 - 1][y2] == '=') player2State++;
    }
    else if (y2 == size - 1)
    {
        player2State++;
        if (board[x2][y2- 1] == '|') player2State++;
        if (board[x2 + 1][y2] == '=') player2State++;
        if (board[x2 - 1][y2] == '=') player2State++;
    }
    else
    {
        if (board[x2 + 1][y2] == '=') player2State++;
        if (board[x2 - 1][y2] == '=') player2State++;
        if (board[x2][y2+ 1] == '|') player2State++;
        if (board[x2][y2- 1] == '|') player2State++;
    }

    if (model == 'h') 
    {
        board[x][y + 1] = ' ';
        board[x][y - 1] = ' ';
    }
    else
    {
        board[x + 1][y] = ' ';
        board[x - 1][y] = ' ';
    }

    if (player2State < 4) return 1;
    else return 0;
}
