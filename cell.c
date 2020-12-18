#include <time.h>
#include "keyboard.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    unsigned int w = 24, h = 52, count = 0, restart = 0;
    if (argc == 2) w = atoi(argv[1]);
    else if (argc > 2) 
    {
        w = atoi(argv[1]);
        h = atoi(argv[2]);
    }

    const unsigned int width = w, height = h;
    int cells[width][height], bufferCells[width][height];
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            bufferCells[x][y] = rand() % 2;
        }
    }
    //Start loop
    while(1)
    {
        system("clear");
        printf("-------------TERMINAL CELULAR AUTOMATA-------------\n");  
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                count = 0;
                cells[x][y] = bufferCells[x][y];

                //Calculate next state for the grid
                if (x + 1 < width && cells[x+1][y] == 1) count ++;
                if (x + 1 < width && y - 1 >= 0 && cells[x+1][y-1] == 1) count ++;
                if (y - 1 >= 0 && cells[x][y-1] == 1) count ++;
                if (x - 1 >= 0 && y - 1 >= 0 && cells[x-1][y-1] == 1) count ++;
                if (x - 1 >= 0 && cells[x-1][y] == 1) count ++;
                if (x - 1 >= 0 && y + 1 < height && cells[x-1][y+1] == 1) count ++;
                if (y + 1 < height && cells[x][y+1] == 1) count ++;
                if (x + 1 < width && y + 1 < height && cells[x+1][y+1] == 1) count ++;

                if (restart == 1)
                {
                    bufferCells[x][y] = rand() % 2;
                }
                else if (cells[x][y] == 0)
                {
                    if (count == 3) bufferCells[x][y] = 1;
                    else bufferCells[x][y] = 0;
                    printf(" ");
                }
                else 
                {
                    if (count >= 2 && count <= 3) bufferCells[x][y] = 1;
                    else bufferCells[x][y] = 0;
                    printf("▒");
                }
            }
            printf("\n");
        }
        printf("-- Press 'ESC' or 'q' to exit and 'r' to restart. --\n");
        restart = 0;
        int key = keysPressed();
        if (key == 27 || key == 113) return 0;
        if (key == 114) restart = 1;
        usleep(50000); 
    }
    return 0;
}
