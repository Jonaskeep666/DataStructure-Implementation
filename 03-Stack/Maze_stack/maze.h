#ifndef _MAZE_H_
#define _MAZE_H_

#define MazeW 15
#define MazeH 11

#define MazeC  MazeW+2
#define MazeR  MazeH+2

#define MAX (MazeR*MazeC)

typedef struct{
    int rdir;
    int cdir;
}offsets;   //for move[8]

typedef struct {
    int r;
    int c;
    int dir;
} item;     //for path record stack

typedef item StackType;

typedef struct{
    StackType data[MAX];
    int top;
}Stack;

typedef int status;
void ClearStack(Stack*);
status isEmpty(Stack*);
status isFull(Stack*);
StackType Top(Stack*);
status Push(Stack*, const StackType);
status Pop(Stack*, StackType*);


typedef int MzType;

void InitialMove(offsets move[8]);
void printMaze(MzType (*m)[MazeC]);
void InitialMaze(MzType (*mz)[MazeC],MzType (*m)[MazeC]);
void printPath(Stack*);
void path(MzType (*m)[MazeC],MzType (*mz)[MazeC]);

#endif
