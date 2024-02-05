// rewards.c

#include "game.h"

extern char **board;
extern int player1Blocked;
extern int player2Blocked;

void usingReward(gameInfo *game, int player)
{
    int state = generateRandomNumber(1, 20);

    setTextColor(LIGHT_BLUE);

    if (player == 1)
    {
        int x = game->position1[0];
        int y = game->position1[1];
        
        if (state % 2 == 0) // Add walls to user
        {
            int wall = generateRandomNumber(1, 3);

            if (wall == 1)
            {
                game->countWall1 += 2;
                printf("%s, 2 walls has added to your walls!🔥\n", game->player1Name);
            }
            else if (wall == 2)
            {
                game->countWall1 += 3;
                printf("%s, 3 walls has added to your walls!🔥\n", game->player1Name);
            }
            else
            {
                game->countWall1 += 5;
                printf("%s, 5 walls has added to your walls!🔥\n", game->player1Name);
            }
        }
        else if (state % 3 == 0) // Remove walls from user
        {
            int removeWall = generateRandomNumber(1, 3);
            
            if (removeWall == 1)
            {
                game->countWall1 -= 2;
                printf("%s, You lost 2 walls!💔\n", game->player1Name);
            }
            else if (removeWall == 2)
            {
                game->countWall1 -= 3;
                printf("%s, You lost 3 walls!💔\n", game->player1Name);
            }
            else
            {
                game->countWall1 -= 5;
                printf("%s, You lost 5 walls!💔\n", game->player1Name);
            }
        }
        else if (state % 5 == 0) // Add wall to user and remove from opponent
        {
            int stolenWall = generateRandomNumber(1, 2);

            if (stolenWall == 1)
            {
                game->countWall1++;
                game->countWall2--;
                printf("You have stolen 1 wall form %s 🤑\n", game->player2Name);
            }
            else
            {
                game->countWall1 += 2;
                game->countWall2 -= 2;
                printf("You have stolen 2 walls form %s 🤑\n", game->player2Name);
            }
        }
        else if (state % 7 == 0) // Remove all walls in the board
        {
            int size = game->size;

            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (board[i][j] == '=') board[i][j] = '-';
                    else if (board[i][j] == '|') board[i][j] = ':';
                }
            }

            printf("All walls has been removed!\n");
        }
        else if (state % 11 == 0) // Block from this turn for 1 or 2 turn(s)
        {
            int block = generateRandomNumber(1, 2);

            player1Blocked = block;

            printf("%s, You have been blocked for %d turn(s) 🤕\n", game->player1Name, block);

        }
        else if (state % 13 == 0) // Guess the number and win!
        {
            int secretNumber = generateRandomNumber(1, 100);
            int userGuess;

            printf("I'll generate a number, If you guess it correctly, you'll be the winner in this game 🥶\n");

            printf("Guess a number between 1 to 100: ");
            scanf("%d", &userGuess);

            if (secretNumber == userGuess)
            {
                game->position1[0] = 0;
            }
        }
    }
    else
    {
        if (state % 2 == 0)
        {
            int wall = generateRandomNumber(1, 3);

            if (wall == 1)
            {
                game->countWall2 += 2;
                printf("%s, 2 walls has added to your walls!🔥\n", game->player2Name);
            }
            else if (wall == 2)
            {
                game->countWall2 += 3;
                printf("%s, 3 walls has added to your walls!🔥\n", game->player2Name);
            }
            else
            {
                game->countWall2 += 5;
                printf("%s, 5 walls has added to your walls!🔥\n", game->player2Name);
            }
        }
        else if (state % 3 == 0)
        {
            int removeWall = generateRandomNumber(1, 3);
            
            if (removeWall == 1)
            {
                game->countWall2 -= 2;
                printf("%s, You lost 2 walls!💔\n", game->player2Name);
            }
            else if (removeWall == 2)
            {
                game->countWall2 -= 3;
                printf("%s, You lost 3 walls!💔\n", game->player2Name);
            }
            else
            {
                game->countWall2 -= 5;
                printf("%s, You lost 5 walls!💔\n", game->player2Name);
            }
        }
        else if (state % 5 == 0)
        {
            int stolenWall = generateRandomNumber(1, 2);
            
            if (stolenWall == 1)
            {
                game->countWall2++;
                game->countWall1--;
                printf("You have stolen 1 wall form %s 🤑\n", game->player1Name);
            }
            else
            {
                game->countWall2 += 2;
                game->countWall1 -= 2;
                printf("You have stolen 2 walls form %s 🤑\n", game->player1Name);
            }
        }
        else if (state % 7 == 0)
        {
            int size = game->size;

            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (board[i][j] == '=') board[i][j] = '-';
                    else if (board[i][j] == '|') board[i][j] = ':';
                }
            }

            printf("All walls has been removed!\n");
        }
        else if (state % 11 == 0)
        {
            int block = generateRandomNumber(1, 2);

            player2Blocked = block;

            printf("%s, You have been blocked for %d turn(s) 🤕\n", game->player2Name, block);
        }
        else if (state % 13 == 0 && game->player2Sign != 'C')
        {
            int secretNumber = generateRandomNumber(1, 100);
            int userGuess;
            int size = game->size;

            printf("I'll generate a number, If you guess it correctly, you'll be the winner in this game 🥶\n");

            printf("Guess a number between 1 to 100: ");
            scanf("%d", &userGuess);

            if (secretNumber == userGuess)
            {
                game->position2[0] = size - 1;
            }
        }
    }
}