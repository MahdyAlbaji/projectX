// main.c

#include "game.h"

char **board;

gameInfo game;

int player1Blocked, player2Blocked;


int main()
{
    srand(time(NULL));

    setTextColor(LIGHT_RED);
    printf("❤️Welcome to Qouridor!❤️\n");

    int continueGame, userSize, realSize, playerType, wall , classicModern;

    FILE *saveFile = game.file;
    
    strcpy(game.fileName, "game.bin");

    if (isFileEmpty(&game) == 0)
    {
        printf("Hi there 😊\nYou have a not finished game, Do you want to continue(1) or start a new game(2)? ");
        scanf("%d", &continueGame);
    }

    if (isFileEmpty(&game) == 0 && continueGame == 1)
    {
        printf("Loading the game...\n");
        load(&game);
        board = loadBoard(&game);
    }
    else
    {
        setTextColor(LIGHT_GREEN);
        printf("Please enter the size of board: ");
        scanf("%d", &userSize); // user size

        realSize = (2 * userSize) - 1; // real size
        game.size = realSize;

        board = (char**)malloc((realSize + 1) * sizeof(char*));

        if (board == NULL)
        {
            printf("We can't allocate this memory for your board...💔\n");
            return 1;
        }

        for (int i = 0; i < realSize; i++)
        {
            board[i] = (char*)malloc((realSize + 1) * sizeof(char));
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

        printf("Human (1) 👨 / Computer 🤖 (2): ");
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

        do
        {
            printf("Count of walls [0-20]: ");
            scanf("%d", &wall);
        } while (wall < 0 || wall > 20);

        game.countWall1 = wall;
        game.countWall2 = wall;

        setTextColor(WHITE);
        printf("-----------------\n\n");

        setTextColor(BLUE);
        printf("Classic game (1) / Modern game [Rewards, Bonus, Spell] (2): ");
        scanf("%d", &classicModern);
        game.typeGame = classicModern;

        printf("Well well well, %s and %s hope to enjoy.😇\n", &game.player1Name, &game.player2Name);

        initializeGame(&game, userSize);
    }

    printBoard(&game);

    if (classicModern == 1)
    {
        while (1)
        {
            //delOldData(saveFile);

            save(&game);

            setTextColor(PURPLE);
            printf("\n%s turn...(%c)\n", &game.player1Name, game.player1Sign);

            playGameHuman(&game, 1);

            printBoard(&game);
            printf("\n");

            checkWinner(&game);

            setTextColor(LIGHT_GREEN);
            printf("\n%s turn...(%c)\n", &game.player2Name, game.player2Sign);

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
    }
    else
    {
        // Modern game

        while (1)
        {
            //delOldData(saveFile);

            save(&game);

            if (player1Blocked == 0)
            {
                usingReward(&game, 1);

                setTextColor(PURPLE);
                printf("\n%s turn...(%c)\n", &game.player1Name, game.player1Sign);

                playGameHuman(&game, 1);

                printBoard(&game);
                printf("\n");

                checkWinner(&game);
            }
            else
            {
                player1Blocked--;
            }

            if (player2Blocked == 0)
            {
                usingReward(&game, 2);
                
                setTextColor(LIGHT_GREEN);
                printf("\n%s turn...(%c)\n", &game.player2Name, game.player2Sign);

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
            else 
            {
                player2Blocked--;
            }
        }
    }

    return 0;
}

