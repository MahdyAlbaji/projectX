// game.c

#include "game.h"

extern char **board;


int getMove(gameInfo *game, int direction, int player) // 1 --> UP | 2 --> RIGHT | 3 --> DOWN | 4 --> LEFT
{
    char sign1 = game->player1Sign;
    char sign2 = game->player2Sign;
    int size = game->size;

    if (player == 1)
    {
        int x = game->position1[0];
        int y = game->position1[1];

        if (direction == 1)
        {
            if (x - 4 >= 0 && board[x - 2][y] == sign2)
            {
                changePosition(game, player, ' ');
                game->position1[0] -= 4;
                changePosition(game, player, sign1);
                return 1;
            }
            else if (x - 4 < 0)
            {
                changePosition(game, player, ' ');
                game->position1[0] = 0;
                changePosition(game, player, sign1);
                return 1;
            }
            else
            {
                changePosition(game, player, ' ');
                game->position1[0] -= 2;
                changePosition(game, player, sign1);
                return 1;
            }
        }
        else if (direction == 2)
        {
            if (y + 4 < size && board[x][y + 2] == sign2)
            {
                changePosition(game, player, ' ');
                game->position1[1] += 4;
                changePosition(game, player, sign1);
                return 1;
            }
            else if (isValidMove(game, direction, player))
            {
                changePosition(game, player, ' ');
                game->position1[1] += 2;
                changePosition(game, player, sign1);
                return 1;
            }
        }
        else if (direction == 3)
        {
            if (x + 4 < size && board[x + 2][y] == sign2)
            {
                changePosition(game, player, ' ');
                game->position1[0] += 4;
                changePosition(game, player, sign1);
                return 1;
            }
            else
            {
                changePosition(game, player, ' ');
                game->position1[0] += 2;
                changePosition(game, player, sign1);
                return 1;
            }
        }
        else if (direction == 4)
        {
            if (y - 4 >= 0 && board[x][y - 4] == sign2)
            {
                changePosition(game, player, ' ');
                game->position1[1] -= 4;
                changePosition(game, player, sign1);
                return 1;
            }
            else if (isValidMove(game, direction, player))
            {
                changePosition(game, player, ' ');
                game->position1[1] -= 2;
                changePosition(game, player, sign1);
                return 1;
            }
        }
    }
    else
    {
        int x = game->position2[0];
        int y = game->position2[1];

        if (direction == 1)
        {
            if (x - 4 >= 0 && board[x - 2][y] == sign1)
            {
                changePosition(game, player, ' ');
                game->position2[0] -= 4;
                changePosition(game, player, sign2);
                return 1;
            }
            else if (isValidMove(game, direction, player))
            {
                changePosition(game, player, ' ');
                game->position2[0] -= 2;
                changePosition(game, player, sign2);
                return 1;
            }
        }
        else if (direction == 2)
        {
            if (y + 4 < size && board[x][y + 2] == sign1)
            {
                changePosition(game, player, ' ');
                game->position2[1] += 4;
                changePosition(game, player, sign2);
                return 1;
            }
            else if (isValidMove(game, direction, player))
            {
                changePosition(game, player, ' ');
                game->position2[1] += 2;
                changePosition(game, player, sign2);
                return 1;
            }
        }
        else if (direction == 3)
        {
            if (x + 4 < size && board[x + 2][y] == sign1)
            {
                changePosition(game, player, ' ');
                game->position2[0] += 4;
                changePosition(game, player, sign2);
                return 1;
            }
            else if (x + 4 >= size)
            {
                changePosition(game, player, ' ');
                game->position2[0] = size - 1;
                changePosition(game, player, sign2);
                return 1;
            }
            else
            {
                changePosition(game, player, ' ');
                game->position2[0] += 2;
                changePosition(game, player, sign2);
                return 1;
            }
        }
        else if (direction == 4)
        {
            if (y - 4 >= 0 && board[x][y - 2] == sign1)
            {
                changePosition(game, player, ' ');
                game->position2[1] -= 4;
                changePosition(game, player, sign2);
                return 1;
            }
            else if (isValidMove(game, direction, player))
            {
                changePosition(game, player, ' ');
                game->position2[1] -= 2;
                changePosition(game, player, sign2);
                return 1;
            }
        }
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

void playGameHuman(gameInfo *game, int player)
{
    int moveWall;
    int direction;
    char ver_hor;
    int x, y;

    do
    {
        printf("Move (1) / Wall (2): ");
        scanf("%d", &moveWall);
        getchar();

        if (moveWall == 1)
        {
            do
            {
                printf("Direction (You can use arrow keys in your keyboard for moving!)\n");
                if (getch() == 224)
                {
                    switch(getch()) {
                        case 72:
                            direction = 1;
                            break;
                        case 77:
                            direction = 2;
                            break;
                        case 80:
                            direction = 3;
                            break;
                        case 75:
                            direction = 4;
                            break;
                    }
                }
            } while (!isValidMove(game, direction, player));
        }
        else if (moveWall == 2)
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
            } while (!isValidWall(game, x, y, ver_hor) || !pseudoDFS(game, x, y, ver_hor, player));
        }
    } while (moveWall != 1 && moveWall != 2);
    
    if (moveWall == 1)
    {
        if (getMove(game, direction, player));
        else playGameHuman(game, player);
    }
    else if (moveWall == 2)
    {
        if (player == 1) game->countWall1--;
        else game->countWall2--;
        getWall(game, x, y, ver_hor);
    }
}
