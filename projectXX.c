#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>


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

int main()
{
	int n;
	setTextColor(LIGHT_GREEN);
	printf("abad board ra vared konod:");
	scanf("%d",&n);
	
	char board[n][n];
	
	int player1_row,player1_col,player2_row,player2_col;
	setTextColor(BLUE);
	printf("mogheiyat player aval(row and column) :");
	scanf("%d %d",&player1_row,&player1_col);
	setTextColor(BLUE);
	printf("mogheiyat player dovom (row and column) :");
	scanf("%d %d",&player2_row,&player2_col);
	
	player1_row -= 1;
    player1_col -= 1;//BARAYE INKE ARRAYE AZ 0 SHORO MISHE
    player2_row -= 1;
    player2_col -= 1;
    
	int i,j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
		{
			board[i][j] = ' ';
		}
	}
	board[player1_row][player1_col] = '$'; // marker of player1
	board[player2_row][player2_col] = '#'; // marker of player2
	
	int numWalls;
	setTextColor(RED);
	printf("tedad divar ha ro vared kon :");
	scanf("%d",&numWalls);
	
	for (i=0;i<numWalls;i++)
	{
		int rowW,colW;
		char halat;// vertical(amoodi) or horizontal(ofoghi)
		setTextColor(LIGHT_RED);
        printf("mogheiat divar va halat(row, column, and orientation 'H' or 'V'): ");
        scanf("%d %d %c",&rowW,&colW,&halat);
        rowW -= 1;
        colW -= 1; //array az 0 shoro mishe
        board[rowW][colW] = 'X' ;// marker of wall
        if (halat == 'H')
        {
        	board[rowW][colW+1] = 'X';
		}
		if (halat == 'V')
		{
			board[rowW+1][colW] = 'X';
		}
	}
	printf("\n \a");
	
	for (i=0;i<n;i++)
	{
		for(j=0;j<n+1;j++)
		{
			setTextColor(LIGHT_WHITE);
			printf("- ");
		}
		printf("\n");
		for (j=0;j<n;j++)
		{
			setTextColor(LIGHT_PURPLE);
			printf("|");
			setTextColor( LIGHT_AQUA );
			printf("%c",board[i][j]);
			//printf("|%c", board[i][j]);
		}
		setTextColor(LIGHT_PURPLE);
		printf("|\n");
	}
	for (i=0;i<n+1;i++)
	{
		setTextColor(LIGHT_WHITE);
		printf("- ");
	}
	printf("\n");
	
	
	return 0;
}
