#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
int i,j;
char Board[29][29];

void initializeBoard(int n)
{
    int count = 0;
    for (i = 0; i < 2*n-1; i++) {
        for (j = 0; j < 2*n-1; j++) {
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
    if (n % 2 == 0)
	{
		Board[0][((2*n-1)/2)-1] = '#';
		Board[2*n-2][((2*n-1)/2)-1] = '$';
	}
	else 
	{
		Board[0][((2*n-1)/2)] = '#';
		Board[2*n-2][((2*n-1)/2)] = '$';
	}
}

void printBoard(int n) {
    for (i = 0; i < 2*n-1; i++) {
        for (j = 0; j < 2*n-1; j++) {
            if (j == 0) printf("| ");
            printf("%c", Board[i][j]);
        }
        printf("|\n");
    }
}

int main()
{
	printf("Welcome to Quoridor!\n");
    printf("Sign of player1 is (#)\n");
    printf("Sign of player2 is ($)\n");
    printf("\n");
    printf("Enter board dimensions :\n");
	int n;
	scanf("%d",&n);
	char Board[2 * n - 1][2 * n - 1];
	initializeBoard(n);
	int p1_row,p1_col;
	int p2_row,p2_col;
	if (n % 2 == 0)
	{
	
		p1_row = 0;
		p1_col = ((2*n-1)/2)-1;
		p2_row = 2*n-2;
		p2_col = ((2*n-1)/2)-1;
	}
	else 
	{
		p1_row = 0;
		p1_col = ((2*n-1)/2);
		p2_row = 2*n-2;
		p2_col = ((2*n-1)/2);
	}
	printBoard(n);
	
	
	
	
}
