#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define SIZE 17

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

short setTextColor(const ConsoleColors foreground)
{
    Handle consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    BufferInfo bufferInfo;
    if(!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo))
        return 0;
    Word color = (bufferInfo.wAttributes & 0xF0) + (foreground & 0x0F);
    SetConsoleTextAttribute(consoleHandle, color);
    return 1;
}

char Board[SIZE][SIZE];

void initializeBoard() {
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i % 2 == 0 && j % 2 == 0) Board[i][j] = ' ';
            else if (i % 2 == 0 && j % 2 != 0) Board[i][j] = ':';
            else
            {
                Board[i][j] = '-';
                /*if (count % 2 == 0) Board[i][j] = '-';
                else Board[i][j] = ' ';
                count++;*/
            }
        }
    }
}

void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            setTextColor(PURPLE);
            if (j == 0) printf("| ");
            setTextColor(YELLOW);
            printf("%c", Board[i][j]);
        }
        setTextColor(PURPLE);
        printf("|\n");
    }
}