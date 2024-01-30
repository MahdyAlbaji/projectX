#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define SIZE 17

#include "faze1 (1).c"
extern char Board[SIZE][SIZE];
int i,j;

typedef HANDLE Handle;
typedef CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
typedef WORD Word;

short setTextColor(const ConsoleColors foreground);

int player1_row = 0, player1_col = 8, player2_row = SIZE - 1, player2_col = 8;
char player1_sign = '$', player2_sign = '#';
int wall1 = 10, wall2 = 10;
int direction;

void initializeBoard();

void printBoard();

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
        if (manner == 'V') 
		{
			if (2 * y - 2 >= 9) 
            {
            	y -= 1;
			}
			if ( 2 * x >= 9)
			{
				x -= 1;
			}
			if (Board[2 * x - 1][2 * y - 2]  != '=' && Board[2 * x - 1][2 * y] != '=' )
			{
				Board[x * 2 - 2][2 * y - 1] = '|' ;
				Board[x * 4  - 2 * x][2 * y - 1] = '|';
			}
		}
        else if (manner == 'H')
        {
            if (2 * y - 2 >= 9) 
            {
            	y -= 1;
			}
			if (Board[x * 2 - 2][2 * y - 1] != '|' && Board[x * 4  - 2][2 * y - 1] != '|' )
			{
				Board[2 * x - 1][2 * y - 2] = '=';
            	Board[2 * x - 1][2 * y] = '=';
			}
			
        }
        wall1--;
    } else if (player == 2 && wall2 > 0) {
        if (manner == 'V')
		{
			if (2 * y - 2 >= 9) 
            {
            	y -= 1;
			}
			if ( 2 * x >= 9)
			{
				x -= 1;
			}
			if (Board[2 * x - 1][2 * y - 2]  != '=' && Board[2 * x - 1][2 * y] != '=' )
			{
				Board[x * 2 - 2][2 * y - 1] = '|' ;
				Board[x * 4  - 2 * x][2 * y - 1] = '|';
			}
		} 
        else if (manner == 'H')
        {
        	if (2 * y - 2 >= 9) 
            {
            	y -= 1;
			}
			if (Board[x * 2 - 2][2 * y - 1] != '|' && Board[x * 4  - 2][2 * y - 1] != '|' )
			{
				Board[2 * x - 1][2 * y - 2] = '=';
            	Board[2 * x - 1][2 * y] = '=';
			}
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

        printf("\nPlayer 1 turn --> Move(1) or Wall(2): ");
        do
        {
        	scanf("%d", &choice);
        	if ( choice == 1 || choice == 2) break;
        	printf("\nPlayer 1 turn --> Move(1) or Wall(2): ");
		}while (choice != 1 || choice != 2);
    
        if (choice == 1) {
            setTextColor(RED); ///// az inja 
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
        } else if (choice == 2) {
            setTextColor(BLUE);
            printf("Enter the manner (V/H): ");
            do
            {
            	scanf(" %c",&manner);
            	if(manner == 'V' || manner == 'H') break;
            	printf("Enter the manner (V/H): ");
			}while (manner != 'V' || manner == 'H');

            manner = toupper(manner);

            setTextColor(LIGHT_AQUA);
			
            printf("Enter the coordinates (x,y) ([1-9],[1-9]): ");
            scanf("%d %d", &x, &y);

            buildWall(1, x, y, manner);
        }
    } else {
        setTextColor(GREEN);

        printf("\nPlayer 2 turn --> Move(1) or Wall(2): \n");
       /* do
        {
        	//scanf("%d", &choice);
        	choice = rand() % 2 + 1;
        	if ( choice == 1 || choice == 2) break;
        	printf("\nPlayer 2 turn --> Move(1) or Wall(2): ");
		}while (choice != 1 || choice != 2);*/
		choice = rand() % 2 + 1;
        if (choice == 1) {
            setTextColor(RED);

            /*printf("Play with Arrows keys!\n");
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
            }*/
            direction = rand() % 4 + 1;
             
            move(2, player2_row, player2_col, direction);
        } else if (choice == 2) {
            setTextColor(BLUE);

            //printf("\nEnter the manner (V/H): ");
            do
            {
            	//scanf(" %c",&manner);
            	char chs[] = "HVHVHVHVHVHVHVHVHV";
				char s[11];
				srand(time(0));
				for (i = 0; i < 10;i++)
				{
					s[i] = chs[rand() % 26];
				}
				s[10] = 0;
				manner = s[0];
            	if(manner == 'V' || manner == 'H') break;
            	//printf("Enter the manner (V/H): ");
			}while (manner != 'V' || manner == 'H');
            manner = toupper(manner);

            setTextColor(LIGHT_AQUA);

            //printf("\nEnter the coordinates (x,y) ([1-9],[1-9]): \n");
            
            //scanf("%d %d", &x, &y);
            x = rand() % 9 + 1;
            y = rand() % 9 + 1;
            buildWall(2, x, y, manner);
        }
    }

    printBoard();
}

int main() {
    setTextColor(LIGHT_AQUA);
    printf("Welcome to Quoridor!\n");

    setTextColor(LIGHT_RED);
    printf("Sign of player1 is (%c)\n", player1_sign);
    printf("Sign of player2 is (%c)\n", player2_sign);
    printf("\n");

    initializeBoard();
    
    Board[player1_row][player1_col] = player1_sign;
    Board[player2_row][player2_col] = player2_sign;

    printBoard();

    while (checkWinner() == 0)
    {
        play(1);
        if (checkWinner() == 1) {
            printf("Player 1 won!\n");
            exit(1);
        }
        else if (checkWinner() == 2) {
            printf("Player 2 won!\n");
            exit(1);
        }
        play(2);
    }

    return 0;
}
