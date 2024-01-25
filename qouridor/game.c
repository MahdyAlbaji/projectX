// game.c

#include "game.h"

extern char **board;


void changePosition(gameInfo *game, int player, char sign)
{
    if (player == 1) board[game->position1[0]][game->position1[1]] = sign;
    else board[game->position2[0]][game->position2[1]] = sign;
}

int checkWinner(gameInfo *game)
{
    if (game->position1[0] == 0)
    {
        return 1;   
    }
    else if (game->position2[0] == game->size - 1)
    {
        return 2;
    }
}

int getMove(gameInfo *game, int direction, int player) // 1 --> UP | 2 --> RIGHT | 3 --> DOWN | 4 --> LEFT
{
    if (player == 1)
    {
        char sign = game->player1Sign;

        if (direction == 1)
        {
            changePosition(game, player, ' ');
            game->position1[0] -= 2;
            changePosition(game, player, sign);
        }
        else if (direction == 2)
        {
            changePosition(game, player, ' ');
            game->position1[1] += 2;
            changePosition(game, player, sign);
        }
        else if (direction == 3)
        {
            changePosition(game, player, ' ');
            game->position1[0] += 2;
            changePosition(game, player, sign);
        }
        else if (direction == 4)
        {
            changePosition(game, player, ' ');
            game->position1[1] -= 2;
            changePosition(game, player, sign);
        }
    }
    else
    {
        char sign = game->player2Sign;
        if (direction == 1)
        {
            changePosition(game, player, ' ');
            game->position2[0] -= 2;
            changePosition(game, player, sign);
        }
        else if (direction == 2)
        {
            changePosition(game, player, ' ');
            game->position2[1] += 2;
            changePosition(game, player, sign);
        }
        else if (direction == 3)
        {
            changePosition(game, player, ' ');
            game->position2[0] += 2;
            changePosition(game, player, sign);
        }
        else if (direction == 4)
        {
            changePosition(game, player, ' ');
            game->position2[1] -= 2;
            changePosition(game, player, sign);
        }
    }
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
        } while (!isValidMove(game, direction, player));
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
        } while (!isValidWall(game, x, y, ver_hor) || !pseudoDFS(game, player));
    }
    
    if (move_wall == 1)
    {
        getMove(game, direction, player);
    }
    else
    {
        if (player == 1) game->count_wall1--;
        else game->count_wall2--;
        getWall(game, x, y, ver_hor);
    }

}