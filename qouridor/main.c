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
    int firstSign;
    setTextColor(LIGHT_YELLOW);
    printf("You can choose from these signs:  %c(1) %c(2) %c(3) %c(4) or every sign you want \n",64-58,64-59,64-60,64-61);
    printf("Player1 sign: ");
    scanf("%d",&firstSign);
    if (firstSign == 1)
    {
        game.player1Sign = 64-58;
    }
    else if (firstSign == 2)
    {
        game.player1Sign = 64-59;
    }
    else if (firstSign == 3)
    {
        game.player1Sign = 64-60;
    }
    else if (firstSign == 4)
    {
        game.player1Sign = 64-61;
    }
    else 
    {
        scanf("%c", &game.player1Sign);
        getchar();
    }
    setTextColor(YELLOW);
    do
    {
        if (playerType == 1)
        {
            printf("Player2 name: ");
            scanf("%s", game.player2Name);
            getchar();
            printf("You can choose from these signs:  %c(1) %c(2) %c(3) %c(4) or every sign you want\n",64-58,64-59,64-60,64-61);
            printf("Player2 sign: ");
            int firstSign;
            scanf("%d",&firstSign);
            if (firstSign == 1)
            {
                game.player2Sign = 64-58;
            }
            else if (firstSign == 2)
            {
                game.player2Sign = 64-59;
            }
            else if (firstSign == 3)
            {
                game.player2Sign = 64-60;
            }
            else if (firstSign == 4)
            {
                game.player2Sign = 64-61;
            }
            else 
            {
            scanf("%c", &game.player2Sign);
            getchar();
            }
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
    int type;
    setTextColor(LIGHT_YELLOW);
    printf("Choose the type of game (classic(1) or new(2)(with bonus and spells)) : \n");
    scanf("%d",&type);
    printf("-----------------\n\n");

    initializeGame(&game, userSize);

    printBoard(&game);
    if (type == 1)
    {
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
    }
    else if (type == 2)
    {
        while (1)
        {
            int prize = rand() % 2 + 1; // prize == 1 good && prize == 2 bad
            setTextColor(PURPLE);
            printf("\n%s turn...\n", &game.player1Name);
            if (prize == 1)
            {
                printf("You won an award\n");
                int x = rand() % 5;
                if (x == 0) 
                {
                    printf("Added 2 walls \n");
                    game.count_wall1 += 2;
                    playGameHuman(&game, 1);
                }
                else if (x == 1)
                {
                    printf("Added 3 walls \n");
                    game.count_wall1 += 3;
                    playGameHuman(&game, 1);
                }
                else if (x == 2)
                {
                    printf("Added 5 walls \n");
                    game.count_wall1 += 5;
                    playGameHuman(&game, 1);
                }
                else if (x == 3)
                {
                    printf("Your opponent lost 1 walls \n");
                    game.count_wall2 -= 1;
                    playGameHuman(&game, 1);
                }
                else if (x == 4)
                {
                    printf("Your opponent lost 2 walls \n");
                    game.count_wall2 -= 2;
                    playGameHuman(&game, 1);
                }
            }
            else if (prize == 2)
            {
                printf("You are enchanted \n");
                int x = rand() % 4;
                if (x == 0)
                {
                    printf("You lost 2 walls \n");
                    game.count_wall1 -= 2;
                    playGameHuman(&game, 1);
                }
                else if (x == 1)
                {
                    printf("You lost 3 walls \n");
                    game.count_wall1 -= 3;
                    playGameHuman(&game, 1);
                }
                else if (x == 2)
                {
                    printf("You lost 5 walls \n");
                    game.count_wall1 -= 5;
                    playGameHuman(&game, 1);
                }
                else if(x == 3)
                {
                    printf("Your turn was missed \n");
                    playGameHuman(&game, 3);
                }
            }
            //playGameHuman(&game, 1);

            printBoard(&game);
            printf("\n");

            checkWinner(&game);

            setTextColor(LIGHT_GREEN);
            printf("\n%s turn...\n", &game.player2Name);
            if (playerType == 1)
            {
                if (prize == 1)
                {
                    printf("You won an award\n");
                    int x = rand() % 5;
                    if (x == 0) 
                    {
                        printf("Added 2 walls \n");
                        game.count_wall2 += 2;
                        playGameHuman(&game, 2);
                    }
                    else if (x == 1)
                    {
                        printf("Added 3 walls \n");
                        game.count_wall2 += 3;
                        playGameHuman(&game, 2);
                    }
                    else if (x == 2)
                    {
                        printf("Added 5 walls \n");
                        game.count_wall2 += 5;
                        playGameHuman(&game, 2);
                    }
                    else if (x == 3)
                    {
                        printf("Your opponent lost 1 walls \n");
                        game.count_wall1 -= 1;
                        playGameHuman(&game, 2);
                    }
                    else if (x == 4)
                    {
                        printf("Your opponent lost 2 walls \n");
                        game.count_wall1 -= 2;
                        playGameHuman(&game, 2);
                    }
                }
                else if (prize == 2)
                {
                    printf("You are enchanted \n");
                    int x = rand() % 4;
                    if (x == 0)
                    {
                        printf("You lost 2 walls \n");
                        game.count_wall2 -= 2;
                        playGameHuman(&game, 2);
                    }
                    else if (x == 1)
                    {
                        printf("You lost 3 walls \n");
                        game.count_wall2 -= 3;
                        playGameHuman(&game, 2);
                    }
                    else if (x == 2)
                    {
                        printf("You lost 5 walls \n");
                        game.count_wall2 -= 5;
                        playGameHuman(&game, 2);
                    }
                    else if (x == 3)
                    {
                        printf("Your turn was missed \n");
                        playGameHuman(&game, 3);
                    }
                }
            }
            else
            {
                if (prize == 1)
                {
                    printf("Computer won an award\n");
                    int x = rand() % 5;
                    if (x == 0) 
                    {
                        printf("Added 2 walls to Computer \n");
                        game.count_wall2 += 2;
                        playGameComputer(&game, 2);
                    }
                    else if (x == 1)
                    {
                        printf("Added 3 walls to Computer \n");
                        game.count_wall2 += 3;
                        playGameComputer(&game, 2);
                    }
                    else if (x == 2)
                    {
                        printf("Added 5 walls to Computer \n");
                        game.count_wall2 += 5;
                        playGameComputer(&game, 2);
                    }
                    else if (x == 3)
                    {
                        printf("Your opponent lost 1 walls \n");
                        game.count_wall1 -= 1;
                        playGameComputer(&game, 2);
                    }
                    else if (x == 4)
                    {
                        printf("Your opponent lost 2 walls \n");
                        game.count_wall1 -= 2;
                        playGameComputer(&game, 2);
                    }
                }
                else if (prize == 2)
                {
                    printf("Computer are enchanted \n");
                    int x = rand() % 4;
                    if (x == 0)
                    {
                        printf("Computer lost 2 walls \n");
                        game.count_wall2 -= 2;
                        playGameComputer(&game, 2);
                    }
                    else if (x == 1)
                    {
                        printf("Computer lost 3 walls \n");
                        game.count_wall2 -= 3;
                        playGameComputer(&game, 2);
                    }
                    else if (x == 2)
                    {
                        printf("Computer lost 5 walls \n");
                        game.count_wall2 -= 5;
                        playGameComputer(&game, 2);
                    }
                    else if (x == 3)
                    {
                        printf("Computer turn was missed \n");
                        playGameComputer(&game, 3);
                    }
                }
                //playGameComputer(&game, 2);
            }
            if (game.count_wall1 < 0) /// tedad wall manfi nashe
            {
                game.count_wall1 = 0;
            }   
            else if (game.count_wall2 < 0)
            {
                game.count_wall2 = 0;
            }
            printBoard(&game);
            printf("\n");

            checkWinner(&game);
        }
    }
    return 0;
}

