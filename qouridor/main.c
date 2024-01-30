// main.c

#include "game.h"

char **board;
gameInfo game;


int main()
{
    srand(time(NULL));

    setTextColor(LIGHT_RED);
    printf("Welcome to Qouridor!\n");

    int userSize, realSize;
    
    setTextColor(LIGHT_GREEN);
    printf("Please enter the size of board: ");
    scanf("%d", &userSize); // user size

    realSize = (2 * userSize) - 1; // real size
    game.size = realSize;

    board = (char**)malloc(realSize * sizeof(char*));

    if (board == NULL)
    {
        printf("We can't allocate this memory for your board...\n");
        return 1;
    }

    for (int i = 0; i < realSize; i++)
    {
        board[i] = (char*)malloc(realSize * sizeof(char));
    }

    for (int i = 0; i < realSize; i++)
    {
        for (int j = 0; j < realSize; j++)
        {
            if (i % 2 == 0 && j % 2 == 0) board[i][j] = ' ';
            else if (i % 2 != 0 && j % 2 == 0) board[i][j] = '-';
            else if (i % 2 != 0 && j % 2 != 0) board[i][j] = '+';
            else if (i % 2 == 0 && j % 2 != 0) board[i][j] = ':';
        }
    }

    int playerType;
    printf("Human (1)/ Computer (2): ");
    scanf("%d", &playerType);
    getchar();

    setTextColor(AQUA);
    printf("Please enter the information of players\n");
    setTextColor(WHITE);
    printf("-----------------\n");

    setTextColor(PURPLE);
    printf("Player1 name: ");
    scanf("%s", game.player1Name);
    getchar();

    printf("Player1 sign: ");
    scanf("%c", &game.player1Sign);
    getchar();

    setTextColor(YELLOW);
    do
    {
        if (playerType == 1)
        {
            printf("Player2 name: ");
            scanf("%s", game.player2Name);
            getchar();

            printf("Player2 sign: ");
            scanf("%c", &game.player2Sign);
            getchar();
        }
        else if (playerType == 2)
        {
            strcpy(game.player2Name , "Computer");
            game.player2Sign = 'C';

        }
    } while (playerType != 1 && playerType != 2);

    setTextColor(GRAY);
    int wall;

    do
    {
        printf("Count of walls [0-20]: ");
        scanf("%d", &wall);
    } while (wall < 0 || wall > 20);

    game.count_wall1 = wall;
    game.count_wall2 = wall;

    setTextColor(WHITE);
    printf("-----------------\n\n");

    initializeGame(&game, userSize);

    printBoard(&game);

    while (1)
    {
        setTextColor(PURPLE);
        printf("\n%s turn...\n", &game.player1Name);

        playGameHuman(&game, 1);

        printBoard(&game);
        printf("\n");

        checkWinner(&game);

        setTextColor(LIGHT_GREEN);
        printf("\n%s turn...\n", &game.player2Name);

        if (playerType == 1)
        {
            playGameHuman(&game, 2);
        }
        else
        {
            playGameComputer(&game, 2);
        }

        printBoard(&game);
        printf("\n");

        checkWinner(&game);
    }

    return 0;
}

