#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define SIZE 17

#include "faze1.c"
extern char Board[SIZE][SIZE];

/*typedef enum
{
    BLACK = 0, BLUE = 1, GREEN = 2,
    AQUA = 3, RED = 4, PURPLE = 5,
    YELLOW = 6, WHITE = 7, GRAY = 8, 
    LIGHT_BLUE = 9, LIGHT_GREEN = 10,
    LIGHT_AQUA = 11, LIGHT_RED = 12, 
    LIGHT_PURPLE = 13, LIGHT_YELLOW = 14,
    LIGHT_WHITE = 15
} ConsoleColors;*/

typedef HANDLE Handle;
typedef CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
typedef WORD Word;

short setTextColor(const ConsoleColors foreground);

/*short setTextColor(const ConsoleColors foreground) {
    Handle consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    BufferInfo bufferInfo;
    if(!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo))
        return 0;
    Word color = (bufferInfo.wAttributes & 0xF0) + (foreground & 0x0F);
    SetConsoleTextAttribute(consoleHandle, color);
    return 1;
}*/

int player1_row = 0, player1_col = 8, player2_row = SIZE - 1, player2_col = 8;
char player1_sign = '#', player2_sign = '$';
int wall1 = 10, wall2 = 10;
int direction;

void initializeBoard(); /*{
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i % 2 == 0 && j % 2 == 0) Board[i][j] = ' ';
            else if (i % 2 == 0 && j % 2 != 0) Board[i][j] = ':';
            else
            {
                Board[i][j] = '-';
                //if (count % 2 == 0) Board[i][j] = '-';
                //else Board[i][j] = ' ';
                //count++;
            }
        }
    }
}*/

void printBoard(); /*{
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
}*/

int isValidMove(int way, int x, int y) {
    if (way == 1 && x >= 0 && x < SIZE && y >= 0 && y < SIZE && Board[x - 1][y] != '=') return 1;
    else if (way == 2 && x >= 0 && x < SIZE && y >= 0 && y < SIZE && Board[x + 1][y] != '=') return 1;
    else if (way == 3 && x >= 0 && x < SIZE && y >= 0 && y < SIZE && Board[x][y + 1] != '|') return 1;
    else if (way == 4 && x >= 0 && x < SIZE && y >= 0 && y < SIZE && Board[x][y - 1] != '|') return 1;
    else return 0;
}

void move(int player, int x, int y, int direction) {
    if (player == 1 && isValidMove(direction, x, y)) {
        Board[player1_row][player1_col] = ' ';
        if (direction == 1 && isValidMove(direction, x - 2, y))player1_row -= 2;
        else if (direction == 2 && isValidMove(direction, x + 2, y)) player1_row += 2;
        else if (direction == 3 && isValidMove(direction, x, y + 2)) player1_col += 2;
        else if (direction == 4 && isValidMove(direction, x, y - 2)) player1_col -= 2;
        Board[player1_row][player1_col] = player1_sign;
    } else if (player == 2 && isValidMove(direction, x, y)) {
        Board[player2_row][player2_col] = ' ';
        if (direction == 1 && isValidMove(direction, x - 2, y)) player2_row -= 2;
        else if (direction == 2 && isValidMove(direction, x + 2, y)) player2_row += 2;
        else if (direction == 3 && isValidMove(direction, x, y + 2)) player2_col += 2;
        else if (direction == 4 && isValidMove(direction, x, y - 2)) player2_col -= 2;
        Board[player2_row][player2_col] = player2_sign;
    }
}

void buildWall(int player, int x, int y, char manner) {
    if (player == 1 && wall1 > 0) {
        if (manner == 'V') Board[x * 2 - 2][2 * y - 1] = '|';
        else
        {
            Board[2 * x - 1][2 * y - 2] = '=';
            Board[2 * x - 1][2 * y] = '=';
        }
        wall1--;
    } else if (player == 2 && wall2 > 0) {
        if (manner == 'V') Board[x * 2 - 2][2 * y - 1] = '|';
        else
        {
            Board[2 * x - 1][2 * y - 2] = '=';
            Board[2 * x - 1][2 * y] = '=';
        }
        wall2--;
    }
}

int checkWinner() {
    if (player1_row == SIZE - 1) return 1;
    else if (player2_row == 0) return 2;
    return 0;
}

void play(int turn) {
    int choice, x, y;
    char manner;

    if (turn == 1) {
        setTextColor(GREEN);

        printf("Player 1 turn --> Move(1) or Wall(2): ");
        scanf("%d", &choice);

        if (choice == 1) {
            setTextColor(RED);

            //printf("UP(1) | DOWN(2) | RIGHT(3) | LEFT(4): ");
            //scanf("%d", &direction);

            printf("Play with Arrows keys!\n");
            if (getch() == 224) {
                switch(getch()) {
                    case 72:
                        direction = 1;
                        break;
                    case 80:
                        direction = 2;
                        break;
                    case 77:
                        direction = 3;
                        break;
                    case 75:
                        direction = 4;
                        break;
                }
            }
            move(1, player1_row, player1_col, direction);
        } else {
            setTextColor(BLUE);

            printf("Enter the manner (V/H): ");
            scanf(" %c", &manner);

            manner = toupper(manner);

            setTextColor(LIGHT_AQUA);

            printf("Enter the coordinates (x, y): ");
            scanf("%d %d", &x, &y);

            buildWall(1, x, y, manner);
        }
    } else {
        setTextColor(GREEN);

        printf("Player 2 turn --> Move(1) or Wall(2): ");
        scanf("%d", &choice);

        if (choice == 1) {
            setTextColor(RED);

            //printf("UP(1) | DOWN(2) | RIGHT(3) | LEFT(4): ");
            //scanf("%d", &direction);

            printf("Play with Arrows keys!\n");
            if (getch() == 224) {
                switch(getch()) {
                    case 72:
                        direction = 1;
                        break;
                    case 80:
                        direction = 2;
                        break;
                    case 77:
                        direction = 3;
                        break;
                    case 75:
                        direction = 4;
                        break;
                }
            }
             
            move(2, player2_row, player2_col, direction);
        } else {
            setTextColor(BLUE);

            printf("Enter the manner (V/H): ");
            scanf(" %c", &manner);

            manner = toupper(manner);

            setTextColor(LIGHT_AQUA);

            printf("Enter the coordinates (x, y): ");
            scanf("%d %d", &x, &y);

            buildWall(2, x, y, manner);
        }
    }

    printBoard();
}

int main() {
    setTextColor(GRAY);
    printf("Welcome to Quoridor!\n");

    initializeBoard();
    
    Board[player1_row][player1_col] = player1_sign;
    Board[player2_row][player2_col] = player2_sign;

    printBoard();

    while (checkWinner() == 0)
    {
        play(1);
        if (checkWinner() == 1) printf("Player 1 won!\n");
        else if (checkWinner() == 2) printf("Player 2 won!\n");
        play(2);
    }

    return 0;
}
