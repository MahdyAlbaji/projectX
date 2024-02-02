#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateRandomNumber(int low, int high)
{
    int lower = low;
    int upper = high;

    srand(time(NULL));
    int x = (rand() % (upper - lower + 1)) + lower;
    
    return x;
}

int main()
{
    int x = generateRandomNumber(1, 2);
    printf("%d", x);

    return 0;
}