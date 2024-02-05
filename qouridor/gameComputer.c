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
        int direction = 3;

        if (isValidMove(game, direction, player))
        {
            getMove(game, direction, player);
        }
        else 
        {
            do
            {
                direction = rand() % 4 + 1; //generateRandomNumber(1, 4);
                if (isValidMove(game, direction, player)) getMove(game, direction, player);
            }while (!isValidMove(game, direction, player));
        }
        
        

    }
    else // wall
    {
        char model;
        //int state = rand() % 2 + 1; // generateRandomNumber(1, 2);
        //if (state == 1) model = 'h';
        //else model = 'v';

        int x1 = game->position1[0] - 1;
        int y1 = game->position1[1] - 1;
        int x2 = game->position2[0];
        int y2 = game->position2[1];

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
            	char chs[] = "hvhvhvhvhvhvhvhv";
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
            if(isValidWall(game,x1,y1,model))
            {
                if (!isValidWall(game,x2,y2,model))
                {
                    getWall(game, x1, y1,model);
                    game->count_wall2 --;
                }
                else 
                {
                    for (int i = 1;i < size / 2; i++)
                    {
                        if(game->position1[0] == size - i)
                        {
                            getWall(game,size - i, y1, model);
                            game->count_wall2 --;
                            break;
                        }
                    }
                    
                    
                }
            }
            else
            {
                x1 = rand() % size + 1;
                y1 = rand() % size + 1;
                if (isValidWall(game, x1, y1, model)) 
                {
                    getWall(game, x1, y1, model);
                    game->count_wall2 --;
                }
            }
    }
}