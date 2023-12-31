#include <stdio.h>
#include <string.h>

#define SIZE 17

char Board[SIZE][SIZE]; // تعریف تابلو

void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (j % 2 == 0) {
                Board[i][j] = ' ';
            }
            else {
                Board[i][j] = ':';
            }
        }
    }
}

void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c%c", Board[i][j], Board[i][j]); // چاپ هر کاراکتر دوبار
        }
        printf("\n");
    }
}

int main() {
    initializeBoard();
    printBoard();

    return 0;
}
