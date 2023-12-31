#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

#define SIZE 9

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

char Board[SIZE][SIZE * 2 - 1];
int player1_row = 0, player1_col = 8, player2_row = 8, player2_col = 8;
char player1_sign = '#';
char player2_sign = '$';

int turn1 = 1;
int turn2 = 0;

int numWalls = 0;

void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE * 2 - 1; j++) {
            if (j % 2 != 0) Board[i][j] = ':';
            else Board[i][j] = ' ';
        }
    }
}

void printBoard() {
	setTextColor(BLUE);
    printf("--------------------\n");

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE * 2 - 1; j++) {
			setTextColor(BLUE);
            if (j == 0) printf("| ");
			setTextColor(YELLOW);
            printf("%c", Board[i][j]);
        }
		setTextColor(BLUE);
        printf(" |\n");
    }

	setTextColor(BLUE);
    printf("--------------------\n");
}

// formol divar gozashtan --> 2n - 1

int letMove(int x, int y)
{
	// Shart vogod divar monde!
	if (x != player1_row && x != player2_row && x >= 0 && x <= 8 && y != player1_col && y != player2_col && y >= 0 && y <= 8)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void move(int player, int x, int y, int way) // x, y ke alan hast
{
	// Player 1
	if (player = 1 && way == 1 && letMove(x, y) == 1) // UP
	{
		Board[player1_row][player1_col] = ' ';
		player1_row--;
		Board[player1_row][player1_col] = player1_sign;
	}
	else if (player = 1 && way == 2 && letMove(x, y) == 1) // Down
	{
		Board[player1_row][player1_col] = ' ';
		player1_row++;
		Board[player1_row][player1_col] = player1_sign;
	}
	else if (player = 1 && way == 3 && letMove(x, y) == 1) // Right
	{
		Board[player1_row][player1_col] = ' ';
		player1_col++;
		Board[player1_row][player1_col] = player1_sign;
	}
	else if (player = 1 && way == 4 && letMove(x, y) == 1) // Left
	{
		Board[player1_row][player1_col] = ' ';
		player1_col--;
		Board[player1_row][player1_col] = player1_sign;
	}
	// Player 2
	else if (player = 2 && way == 1 && letMove(x, y) == 1) // UP
	{
		Board[player2_row][player2_col] = ' ';
		player2_row--;
		Board[player2_row][player2_col] = player2_sign;
	}
	else if (player = 2 && way == 2 && letMove(x, y) == 1) // Down
	{
		Board[player2_row][player2_col] = ' ';
		player2_row++;
		Board[player2_row][player2_col] = player2_sign;
	}
	else if (player = 2 && way == 3 && letMove(x, y) == 1) // Right
	{
		Board[player2_row][player2_col] = ' ';
		player2_col++;
		Board[player2_row][player2_col] = player2_sign;
	}
	else if (player = 2 && way == 4 && letMove(x, y) == 1) // Left
	{
		Board[player2_row][player2_col] = ' ';
		player2_col--;
		Board[player2_row][player2_col] = player2_sign;
	}
}

void wall(int player, int x, int y)
{

}

int checkWinner()
{
	if (player1_row == SIZE - 1) return 1;
	else if (player2_row == 0) return 2;
	else return 0;
}

void play(int turn)
{
	int move_or_wall;
	int way;
	int xwall, ywall;

	if (turn == 1)
	{
		printf("Player1 turn...");
		printf("Move(1) or Wall(2): ");
		scanf("%d", &move_or_wall);

		if (move_or_wall == 1)
		{
			printf("UP(1) | DOWN(2) | RIGHT(3) | LEFT(4) : ");
			scanf("%d", &way);

			move(1, player1_row, player1_col, way);
		}
		else
		{
			printf("Enter the coordinate of the wall (x, y): ");
			scanf("%d%d", &xwall, &ywall);

			xwall = (xwall * 2) - 1;
			ywall = (ywall * 2) - 1;

			wall(1, xwall, ywall);
		}
		turn1 = 0;
		turn2 = 1;
	}
	else
	{
		printf("Player2 turn...");
		printf("Move(1) or Wall(2): ");
		scanf("%d", &move_or_wall);

		if (move_or_wall == 1)
		{
			printf("UP(1) | DOWN(2) | RIGHT(3) | LEFT(4) : ");
			scanf("%d", &way);

			move(2, player2_row, player2_col, way);
		}
		else
		{
			printf("Enter the coordinate of the wall (x, y): ");
			scanf("%d%d", &xwall, &ywall);

			xwall = (xwall * 2) - 1;
			ywall = (ywall * 2) - 1;
			
			wall(2, xwall, ywall);
		}
		turn1 = 1;
		turn2 = 0;
	}

	if (checkWinner() == 1)
	{
		setTextColor(PURPLE);
		printf("Player1 won!\n");
	}
	else if (checkWinner() == 2)
	{
		setTextColor(PURPLE);
		printf("Player2 won!\n");
	}


	printBoard();
}

int main()
{
	char playerName[20];

	setTextColor(LIGHT_GREEN);

	printf("Welcome to the Quoridor!\n");
	printf("Please enter your name: ");
	scanf("%s", &playerName);

	printf("How many walls does each player have? ");
	scanf("%d",&numWalls);

	initializeBoard();

	Board[player1_row][player1_col] = player1_sign;
	Board[player2_row][player2_col] = player2_sign;

	printBoard();

	while (checkWinner() == 0)
		play(1);
	
	setTextColor(WHITE);
	return 0;
}
