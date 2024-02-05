// board.c

#include "game.h"

extern char **board;

extern int player1Blocked;

extern int player2Blocked;


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

    player1Blocked = 0;
    player2Blocked = 0;
}

void printBoard(gameInfo *game)
{
    printf("\n");

    int size = game->size;

    int len1 = strlen(game->player1Name);
    int len2 = strlen(game->player2Name);

    int countSpaces;
    
    setTextColor(RED);
    if (len1 > len2)
    {
        countSpaces = len1 - len2;

        printf("%s's walls: ", game->player1Name);
        for (int i = 0; i < game->countWall1; i++) printf("| ");

        printf("\n%s's walls: ", game->player2Name);
        for (int i = 0; i < countSpaces; i++) printf(" ");
        for (int i = 0; i < game->countWall2; i++) printf("| ");
    }
    else
    {
        countSpaces = len2 - len1;

        printf("%s's walls: ", game->player1Name);
        for (int i = 0; i < countSpaces; i++) printf(" ");
        for (int i = 0; i < game->countWall1; i++) printf("| ");

        printf("\n%s's walls: ", game->player2Name);
        for (int i = 0; i < game->countWall2; i++) printf("| ");
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
        printf("Congratulations to %s who is the winner!🥳🥳🥳\n", game->player1Name);
        setTextColor(WHITE);

        remove(game->fileName);

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
        printf("Congratulations to %s who is the winner!🥳🥳🥳\n", game->player2Name);
        setTextColor(WHITE);

        remove(game->fileName);

        for (int i = 0; i < size; i++)
        {
            free(board[i]);
        }

        free(board);
        
        exit(0);
    }
}

void copyBoard(gameInfo *game, char **loadBoard, int model)
{
    int size = game->size;

    if (model == 1)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                loadBoard[i][j] = game->bg[i][j];
            }
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                game->bg[i][j] = loadBoard[i][j];
            }
        }
    }
}

void save(gameInfo *game)
{
    int size = game->size;

    copyBoard(game, board, 2);

    FILE *saveFile = fopen(game->fileName, "wb");

    if (saveFile == NULL)
    {
        perror("opening file for writing");
        return;
    }

    fwrite(game, sizeof(gameInfo), 1, saveFile);

    fclose(saveFile);
}

void load(gameInfo *game)
{
    int size = game->size;

    FILE *loadFile = fopen(game->fileName, "rb");

    if (loadFile == NULL)
    {
        perror("Error opening file for reading");
        return;
    }

    fread(game, sizeof(gameInfo), 1, loadFile);

    copyBoard(game, board, 1);

    fclose(loadFile);
}

int isFileEmpty(gameInfo *game)
{
    FILE *file = fopen(game->fileName, "rb");

    if (file == NULL) {
        printf("There is no saved file...\n");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);

    fclose(file);

    if (size <= 0)
    {
        return 1;
    }
        
    return 0;
}

