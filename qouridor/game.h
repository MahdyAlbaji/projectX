// game.h

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

#define MAX_LEN_NAME 30

extern char **board;
extern int player1Blocked;
extern int player2Blocked;

typedef enum
{
    BLACK = 0, BLUE = 1, GREEN = 2,
    AQUA = 3, RED = 4, PURPLE = 5,
    YELLOW = 6, WHITE = 7, GRAY = 8, 
    LIGHT_BLUE = 9, LIGHT_GREEN = 10,
    LIGHT_AQUA = 11, LIGHT_RED = 12, 
    LIGHT_PURPLE = 13, LIGHT_YELLOW = 14,
    LIGHT_WHITE = 15
} ConsoleColors;

typedef HANDLE Handle;
typedef CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
typedef WORD Word;

static short setTextColor(const ConsoleColors foreground)
{
    Handle consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    BufferInfo bufferInfo;
    if(!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo))
        return 0;
    Word color = (bufferInfo.wAttributes & 0xF0) + (foreground & 0x0F);
    SetConsoleTextAttribute(consoleHandle, color);
    return 1;
}

typedef struct
{
    int size;
    char player1Sign;
    char player2Sign;
    char player1Name[MAX_LEN_NAME];
    char player2Name[MAX_LEN_NAME];
    int position1[2];
    int position2[2];
    int countWall1;
    int countWall2;
} gameInfo;

typedef struct
{
    int reward11;
    int reward12;
    int reward13;
    int reward14;
    int reward15;

    int reward21;
    int reward22;
    int reward23;
    int reward24;
    int reward25;
} rewardStatus;

void initializeGame(gameInfo *game, rewardStatus *reward, int userSize);

void printBoard(gameInfo *game);

int isValidMove(gameInfo *game, int direction, int player);

int pseudoDFS(gameInfo *game, int x, int y, char model, int player);

int isValidWall(gameInfo *game, int x, int y, char model);

int checkWinner(gameInfo *game);

void changePosition(gameInfo *game, int player, char sign);

int getMove(gameInfo *game, int direction, int player);

int getWall(gameInfo *game, int x, int y, char model);

// Play computer;

int generateRandomNumber(int low, int high);

void playGameHuman(gameInfo *game, int player);

void playGameComputer(gameInfo *game, int player);

// Rewards

void usingReward(gameInfo *game, rewardStatus *reward, int player);

#endif
