#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

int main(void){
    int mark[MazeR][MazeC];
    int maze[MazeR][MazeC];

    InitialMaze(maze,mark);
    
    path(maze,mark);

    printMaze(maze);
    puts("");
    printMaze(mark);
    puts("");
}
