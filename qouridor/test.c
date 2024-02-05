#include "game.h"

void save(gameInfo *game)
{
    FILE *saveFile = fopen("game.txt", "wt");
    if (saveFile == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    fprintf(saveFile, "%d\n", game->size);
    fprintf(saveFile, "%s %c\n", game->player1Name, game->player1Sign);
    fprintf(saveFile, "%d %d\n", game->position1[0], game->position1[1]);
    fprintf(saveFile, "%s %c\n", game->player2Name, game->player2Sign);
    fprintf(saveFile, "%d %d\n", game->position2[0], game->position2[1]);
    fprintf(saveFile, "%d %d\n", game->countWall1, game->countWall2);

    fclose(saveFile);
}

void load(gameInfo *game)
{
    FILE *loadFile = fopen("game.txt", "rt");
    if (loadFile == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }

    fscanf(loadFile, "%d", &game->size);
    fscanf(loadFile, "%s %c", game->player1Name, &game->player1Sign);
    fscanf(loadFile, "%d %d", &game->position1[0], &game->position1[1]);
    fscanf(loadFile, "%s %c", game->player2Name, &game->player2Sign);
    fscanf(loadFile, "%d %d", &game->position2[0], &game->position2[1]);
    fscanf(loadFile, "%d %d", &game->countWall1, &game->countWall2);

    fclose(loadFile);
}

int main()
{
    
    return 0;
}