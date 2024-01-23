#include <stdio.h>

int main()
{
    char test;
    do
    {
        printf("Enter the input: ");
        test = getc(stdin);
        getchar();
    } while (test != 'w');

    printf("%c", test);
    

    return 0;
}