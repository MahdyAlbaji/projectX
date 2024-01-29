// main.c

#include "game.h"

char **board;
gameInfo game;


int main()
{
    setTextColor(LIGHT_RED);
    printf("Welcome to Qouridor!\n");

    setTextColor(LIGHT_GREEN);
    int userSize, realSize;
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

    int computer_or_human;
    printf("Human (1)/ Computer (2): ");
    scanf("%d", &computer_or_human);
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
        if (computer_or_human == 1)
        {
            printf("Player2 name: ");
            scanf("%s", game.player2Name);
            getchar();

            printf("Player2 sign: ");
            scanf("%c", &game.player2Sign);
            getchar();
        }
        else if (computer_or_human == 2)
        {
            strcpy(game.player2Name , "Computer");
            game.player2Sign = 'C';

        }
    } while (computer_or_human != 1 && computer_or_human != 2);

    setTextColor(GRAY);
    int wall;

    do
    {
        printf("Count of walls [0-15]: ");
        scanf("%d", &wall);
    } while (wall < 0 || wall > 15);

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
        sleep(0.8);

        printBoard(&game);
        printf("\n");

        if (checkWinner(&game) == 1)
        {
            setTextColor(PURPLE);
            printf("%s is the winner!\n", &game.player1Name);
            setTextColor(WHITE);
            break;
        }

        setTextColor(LIGHT_GREEN);
        printf("\n%s turn...\n", &game.player2Name);

        if (computer_or_human == 1)
        {
            playGameHuman(&game, 2);
        }
        else
        {
            playGameComputer(&game, 2);
        }

        printBoard(&game);
        printf("\n");

        if (checkWinner(&game) == 2)
        {
            setTextColor(GREEN);
            printf("%s is the winner!\n", &game.player2Name);
            setTextColor(WHITE);
            break;
        }
    }

    for (int i = 0; i < realSize; i++)
    {
        free(board[i]);
    }

    free(board);

    return 0;
}

