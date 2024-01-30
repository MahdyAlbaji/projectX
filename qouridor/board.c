// board.c

#include "game.h"

extern char **board;


void initializeGame(gameInfo *game, int userSize)
{
    int realSize = game->size;

    if (userSize % 2 == 0)
    {
        game->position1[0] = realSize - 1;
        game->position1[1] = (realSize / 2) + 1;

        game->position2[0] = 0;
        game->position2[1] = (realSize / 2) + 1;
    }
    else
    {
        game->position1[0] = realSize - 1;
        game->position1[1] = realSize / 2;

        game->position2[0] = 0;
        game->position2[1] = realSize / 2;
    }

    board[game->position1[0]][game->position1[1]] = game->player1Sign;
    board[game->position2[0]][game->position2[1]] = game->player2Sign;
}

void printBoard(gameInfo *game)
{
    printf("\n");

    int size = game->size;

    int len1 = strlen(game->player1Name);
    int len2 = strlen(game->player2Name);

    int count_space;
    
    setTextColor(RED);
    if (len1 > len2)
    {
        count_space = len1 - len2;

        printf("%s's walls: ", game->player1Name);
        for (int i = 0; i < game->count_wall1; i++) printf("| ");

        printf("\n%s's walls: ", game->player2Name);
        for (int i = 0; i < count_space; i++) printf(" ");
        for (int i = 0; i < game->count_wall2; i++) printf("| ");
    }
    else
    {
        count_space = len2 - len1;

        printf("%s's walls: ", game->player1Name);
        for (int i = 0; i < count_space; i++) printf(" ");
        for (int i = 0; i < game->count_wall1; i++) printf("| ");

        printf("\n%s's walls: ", game->player2Name);
        for (int i = 0; i < game->count_wall2; i++) printf("| ");
    }
    
    printf("\n\n");

    setTextColor(AQUA);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == '=' || board[i][j] == '|')
            {
                setTextColor(RED);
                printf(" %c ", board[i][j]);
            }
            else if (board[i][j] == '+')
            {
                setTextColor(LIGHT_YELLOW);
                printf(" %c ", board[i][j]);
            }
            else if (board[i][j] == game->player1Sign)
            {
                setTextColor(PURPLE);
                printf(" %c ", board[i][j]);
            }
            else if (board[i][j] == game->player2Sign)
            {
                setTextColor(GREEN);
                printf(" %c ", board[i][j]);
            }
            else
            {
                setTextColor(AQUA);
                printf(" %c ", board[i][j]);
            }
        }
        printf("\n");
    }
    setTextColor(WHITE);
}

void changePosition(gameInfo *game, int player, char sign)
{
    if (player == 1) board[game->position1[0]][game->position1[1]] = sign;
    else board[game->position2[0]][game->position2[1]] = sign;
}

int checkWinner(gameInfo *game)
{
    int size = game->size;

    if (game->position1[0] == 0)
    {
        setTextColor(PURPLE);
        printf("%s is the winner!\n", game->player1Name);
        setTextColor(WHITE);

        for (int i = 0; i < size; i++)
        {
            free(board[i]);
        }

        free(board);

        exit(0);
    }
    else if (game->position2[0] == game->size - 1)
    {
        setTextColor(GREEN);
        printf("%s is the winner!\n", game->player2Name);
        setTextColor(WHITE);

        for (int i = 0; i < size; i++)
        {
            free(board[i]);
        }

        free(board);
        
        exit(0);
    }
}
