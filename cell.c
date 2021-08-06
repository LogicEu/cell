#include <time.h>
#include "keyboard.h"

// $ gcc -Wall cell.c -o cell 80 40

int main(int argc, char* argv[])
{
    srand(time(NULL));
    int width = 52, height = 24, count = 0, restart = 0, key;
    if (argc > 1) width = atoi(argv[1]);
    if (argc > 2) height = atoi(argv[2]);

    int cells[width][height][2];
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            cells[x][y][0] = rand() % 2;
        }
    }

    while(1) {
        printf("-------------TERMINAL CELULAR AUTOMATA-------------\n");
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cells[x][y][1] = cells[x][y][0];
            }
        }  
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (restart) {
                    cells[x][y][0] = rand() % 2;
                    continue;
                }

                count = 0;
                count += (x + 1 < width && cells[x + 1][y][1]);
                count += (x + 1 < width && y - 1 >= 0 && cells[x + 1][y - 1][1]);
                count += (y - 1 >= 0 && cells[x][y - 1][1]);
                count += (x - 1 >= 0 && y - 1 >= 0 && cells[x - 1][y - 1][1]);
                count += (x - 1 >= 0 && cells[x - 1][y][1]);
                count += (x - 1 >= 0 && y + 1 < height && cells[x - 1][y + 1][1]);
                count += (y + 1 < height && cells[x][y + 1][1]);
                count += (x + 1 < width && y + 1 < height && cells[x + 1][y + 1][1]);
        
                if (!cells[x][y][1]) {
                    if (count == 3) cells[x][y][0] = 1;
                    else cells[x][y][0] = 0;
                    printf(" ");
                } else {
                    if (count >= 2 && count <= 3) cells[x][y][0] = 1;
                    else cells[x][y][0] = 0;
                    printf("█");
                }
            }
            printf("\n");
        }

        printf("-- Press 'ESC' or 'q' to exit and 'r' to restart. --\n");
        restart = 0;
        key = keysPressed();
        if (key == 27 || key == 113) break;
        if (key == 114) restart = 1;

        usleep(50000); 
        system("clear");
    }
    return 0;
}
