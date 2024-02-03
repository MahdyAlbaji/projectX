// gameComputer.c

#include "game.h"

extern char **board;

/*int generateRandomNumber(int low, int high)
{
    
    int lower = low;
    int upper = high;

    int x = (rand() % (upper - lower + 1)) + lower;
    
    return x;
}*/

void playGameComputer(gameInfo *game, int player)
{
    if (player == 3)
    {
        return;
    }
    int move_or_wall = rand() % 2 + 1;  // generateRandomNumber(1, 2); // 1 --> move , 2 --> wall

    if (move_or_wall == 1) // move
    {
        /*int direction = 3;

        if (isValidMove(game, direction, player))
        {
            getMove(game, direction, player);
            return;
        }*/
        int direction;
        do
        {
            direction = rand() % 4 + 1; //generateRandomNumber(1, 4);
            if (isValidMove(game, direction, player)) getMove(game, direction, player);
        }while (!isValidMove(game, direction, player));
        

    }
    else // wall
    {
        char model;
        //int state = rand() % 2 + 1; // generateRandomNumber(1, 2);
        //if (state == 1) model = 'h';
        //else model = 'v';

        int x; //= game->position1[0] - 1;
        int y; //= game->position1[1];

        int size = game->size;
        size /= 2;

        /*if (isValidWall(game, x, y, model))
        {
            getWall(game, x, y, model);
            return;
        }
        
        while (!isValidWall(game, x, y, model))
        {
            x = rand() %  size + 1; //generateRandomNumber(1, size);
            y = rand() % size + 1;//generateRandomNumber(1, size);

            if (isValidWall(game, x, y, model)) getWall(game, x, y, model);
        }*/
            do
            {
            	char chs[] = "hvhvhvhvhvhvhvh";
				char s[11];
				srand(time(0));
				for (int i = 0; i < 10;i++)
				{
					s[i] = chs[rand() % 26];
				}
				s[10] = 0;
				model = s[0];
            	if(model == 'v' || model == 'h') break;
			} while (model != 'v' || model == 'h');
            
            //while (!isValidWall(game, x, y, model))
            {
                x = rand() % size + 1;
                y = rand() % size + 1;
                if (isValidWall(game, x, y, model)) 
                {
                    getWall(game, x, y, model);
                }
            }
    }
}