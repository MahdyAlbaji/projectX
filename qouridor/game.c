// game.c

#include "game.h"

extern char **board;


int isValidMove(gameInfo *game, int direction, int player) // NOT COMPLETE!
{
    return 1;
}

void changePosition(gameInfo *game, int player, char sign)
{
    if (player == 1) board[(*game).position1[0]][(*game).position1[1]] = sign;
    else board[(*game).position2[0]][(*game).position2[1]] = sign;
}

int checkWinner(gameInfo *game)
{
    if ((*game).position1[0] == 0)
    {
        return 1;   
    }
    else if ((*game).position2[0] == (*game).size - 1)
    {
        return 2;
    }
}

int getMove(gameInfo *game, int direction, int player) // 1 --> UP | 2 --> RIGHT | 3 --> DOWN | 4 --> LEFT
{
    if (player == 1)
    {
        char sign = (*game).player1Sign;

        if (direction == 1)
        {
            do
            {
                changePosition(game, player, ' ');
                (*game).position1[0] -= 2;
                changePosition(game, player, sign);
            } while (!isValidMove(game, direction, player));
        }
        else if (direction == 2)
        {
            do
            {
                changePosition(game, player, ' ');
                (*game).position1[1] += 2;
                changePosition(game, player, sign);
            } while (!isValidMove(game, direction, player));
        }
        else if (direction == 3)
        {
            do
            {
                changePosition(game, player, ' ');
                (*game).position1[0] += 2;
                changePosition(game, player, sign);
            } while (!isValidMove(game, direction, player));
        }
        else if (direction == 4)
        {
            do
            {
                changePosition(game, player, ' ');
                (*game).position1[1] -= 2;
                changePosition(game, player, sign);
            } while (!isValidMove(game, direction, player));
        }
    }
    else
    {
        char sign = (*game).player2Sign;
        if (direction == 1)
        {
            do
            {
                changePosition(game, player, ' ');
                (*game).position2[0] -= 2;
                changePosition(game, player, sign);
            } while (!isValidMove(game, direction, player));
        }
        else if (direction == 2)
        {
            do
            {
                changePosition(game, player, ' ');
                (*game).position2[1] += 2;
                changePosition(game, player, sign);
            } while (!isValidMove(game, direction, player));
        }
        else if (direction == 3)
        {
            do
            {
                changePosition(game, player, ' ');
                (*game).position2[0] += 2;
                changePosition(game, player, sign);
            } while (!isValidMove(game, direction, player));
        }
        else if (direction == 4)
        {
            do
            {
                changePosition(game, player, ' ');
                (*game).position2[1] -= 2;
                changePosition(game, player, sign);
            } while (!isValidMove(game, direction, player));
        }
    }
}

int pseudoDFS(gameInfo *game, int player) // NOT OK!
{
    int player1State = 0;
    int player2State = 0;

    if (player == 1)
    {
        if (board[(*game).position1[0] + 1][(*game).position1[1]] == '=') player1State++;
        if (board[(*game).position1[0] - 1][(*game).position1[1]] == '=') player1State++;
        if (board[(*game).position1[0]][(*game).position1[1] + 1] == '|') player1State++;
        if (board[(*game).position1[0]][(*game).position1[1] - 1] == '|') player1State++;

        if (player1State < 4) return 1;
        else return 0;
    }
    else
    {
        if (board[(*game).position2[0] + 1][(*game).position2[1]] == '=') player2State++;
        if (board[(*game).position2[0] - 1][(*game).position2[1]] == '=') player2State++;
        if (board[(*game).position2[0]][(*game).position2[1] + 1] == '|') player2State++;
        if (board[(*game).position2[0]][(*game).position2[1] - 1] == '|') player2State++;

        if (player2State < 4) return 1;
        else return 0;
    }

}

int isValidWall(gameInfo *game, int x, int y, char model)
{
    if (model == 'v')
    {
        return (board[x - 1][y] == ':' && board[x + 1][y] == ':' && x < (2 * (*game).size) && x > 0 && y < (2 * (*game).size) && y > 0);
    }
    else if (model == 'h')
    {
        return (board[x][y - 1] == '-' && board[x][y + 1] == '-' && x < (2 * (*game).size) && x > 0 && y < (2 * (*game).size) && y > 0);
    }
    return 0;
}

int getWall(gameInfo *game, int x, int y, char model)
{
    if (model == 'v')
    {
        board[x - 1][y] = '|';
        board[x + 1][y] = '|';
    }
    else
    {
        board[x][y - 1] = '=';
        board[x][y + 1] = '=';
    }
}

void playGame(gameInfo *game, int player)
{
    int move_wall;
    int direction;
    char ver_hor;
    int x, y;

    do
    {
        printf("Move (1) / Wall (2): ");
        scanf("%d", &move_wall);
        getchar();
    } while (move_wall != 1 && move_wall != 2);

    if (move_wall == 1)
    {
        do
        {
            printf("Direction: ");
            scanf("%d", &direction);
            getchar();
        } while (direction > 4 || direction < 1);
    }
    else if (move_wall == 2)
    {
        do
        {
            printf("Vertical (v) / Horizontal (h): ");
            scanf("%c", &ver_hor);
            getchar();
            printf("Enter (x,y): ");
            scanf("%d %d", &x, &y);
            getchar();
            x = (2 * x) - 1;
            y = (2 * y) - 1;
        } while (!isValidWall(game, x, y, ver_hor));
    }
    
    if (move_wall == 1)
    {
        getMove(game, direction, player);
    }
    else
    {
        if (player == 1) (*game).count_wall1--;
        else (*game).count_wall2--;
        getWall(game, x, y, ver_hor);
    }

}