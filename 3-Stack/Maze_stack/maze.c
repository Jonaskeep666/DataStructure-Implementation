#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

void ClearStack(Stack* s){
    for(int i=0;i<MAX;++i){
        s->data[i].r=0;
        s->data[i].c=0;
        s->data[i].dir=0;
    }
    s->top = -1;
}

status isEmpty(Stack* s){
    return ((s->top == -1) ? 1:0);
}
status isFull(Stack* s){
    return ((s->top == (MAX-1)) ? 1:0);
}

StackType Top(Stack* s){
    return (s->data[s->top]);
}

status Push(Stack* s, const StackType newItem){
    if(isFull(s)) return 1;
    s->top++;
    s->data[s->top]=newItem;
    return 0;
}
status Pop(Stack* s, StackType* popItem){
    if(isEmpty(s)) return 1;
    *popItem = s->data[s->top];
    s->top--;
    return 0;
}

void checkStack(Stack* s){
    if(isEmpty(s)) return;
    char DIR[3]; DIR[2]='\0';
    for(int i=0;i<=s->top;++i){
        switch(s->data[i].dir){
            case 0: DIR[0]='N';DIR[1]=' '; break;
            case 1: DIR[0]='N';DIR[1]='E'; break;
            case 2: DIR[0]='E';DIR[1]=' '; break;
            case 3: DIR[0]='S';DIR[1]='E'; break;
            case 4: DIR[0]='S';DIR[1]=' '; break;
            case 5: DIR[0]='S';DIR[1]='W'; break;
            case 6: DIR[0]='W';DIR[1]=' '; break;
            case 7: DIR[0]='N';DIR[1]='W'; break;
        }
        printf("(%d,%d),[%s]",s->data[i].r,s->data[i].c,DIR);
    }
}

void InitialMove(offsets move[8]){
    //dir=0 -> N
    move[0].rdir = -1; 
    move[0].cdir = 0;
    //dir=1 -> NE
    move[1].rdir = -1;   
    move[1].cdir = 1;
    //dir=2 -> E
    move[2].rdir = 0;   
    move[2].cdir = 1;
    //dir=3 -> SE
    move[3].rdir = 1;   
    move[3].cdir = 1;
    //dir=4 -> S
    move[4].rdir = 1;   
    move[4].cdir = 0;
    //dir=5 -> SW
    move[5].rdir = 1;   
    move[5].cdir = -1;
    //dir=6 -> W
    move[6].rdir = 0;   
    move[6].cdir = -1;
    //dir=7 -> NW
    move[7].rdir = -1;   
    move[7].cdir = -1;
}

void InitialMaze(MzType (*mz)[MazeC],MzType (*m)[MazeC]){
    int maze[MazeH][MazeW]={{0,1,0,0,0,1,1,0,0,0,1,1,1,1,1},
                            {1,0,0,0,1,1,0,1,1,1,0,0,1,1,1},
                            {0,1,1,0,0,0,0,1,1,1,1,0,0,1,1},
                            {1,1,0,1,1,1,1,0,1,1,0,1,1,0,0},
                            {1,1,0,1,0,0,1,0,1,1,1,1,1,1,1},
                            {0,0,1,1,0,1,1,1,0,1,0,0,1,0,1},
                            {0,1,1,1,1,0,0,1,1,1,1,1,1,1,1},
                            {0,0,1,1,0,1,1,0,1,1,1,1,1,0,1},
                            {1,1,0,0,0,1,1,0,1,1,0,0,0,0,0},
                            {0,0,1,1,1,1,1,0,0,0,1,1,1,1,0},
                            {0,1,0,0,1,1,1,1,1,0,1,1,1,1,0}};

    for(int i=1; i<=MazeH; ++i)
        for(int j=1; j<=MazeW; ++j){
            mz[i][j]=maze[i-1][j-1];
            m[i][j]=0;
        }
    for(int i=0;i<MazeC;++i){
        mz[0][i]=1;
        mz[MazeR-1][i]=1;
        m[0][i]=1;
        m[MazeR-1][i]=1;
    }
    for(int i=0;i<MazeR;++i){
        mz[i][0]=1;
        mz[i][MazeC-1]=1;
        m[i][0]=1;
        m[i][MazeC-1]=1;
    }
}

void printMaze(MzType (*m)[MazeC]){
    for(int i=0; i<(MazeR); ++i){
        for(int j=0; j<(MazeC); ++j){
            printf("%d ",(*(m+i))[j]);
        }
        puts("");
    }
}

void printPath(Stack* s){
    if(isEmpty(s)) return;
    StackType popItem={0,0,0};
    char DIR[3]; DIR[2]='\0';
    while(!isEmpty(s)){
        Pop(s,&popItem);
        switch(popItem.dir){
            case 0: DIR[0]='N';DIR[1]=' '; break;
            case 1: DIR[0]='N';DIR[1]='E'; break;
            case 2: DIR[0]='E';DIR[1]=' '; break;
            case 3: DIR[0]='S';DIR[1]='E'; break;
            case 4: DIR[0]='S';DIR[1]=' '; break;
            case 5: DIR[0]='S';DIR[1]='W'; break;
            case 6: DIR[0]='W';DIR[1]=' '; break;
            case 7: DIR[0]='N';DIR[1]='W'; break;
        }
    printf("(%d,%d),[%s]",popItem.r,popItem.c,DIR);
    puts("");
    }
    return;
}

void path(MzType (*mz)[MazeC],MzType (*m)[MazeC]){
    Stack r;         //宣告Stack來紀錄路徑
    ClearStack(&r);     
    offsets move[8];    //宣告方向位移
    InitialMove(move);
    StackType newItem;  //正要推入Stack的元素
    StackType popItem;  //從Stack Pop出來的元素

    int tr=1,tc=1;      //現在位置，初始化為起點
    m[tr][tc]=6;        //標記起點

    int nextr,nextc;    //嘗試下一步的位置
    int dir=2;          //初始化行走方向(E)
    int start=1;        //准許進入迴圈的旗標
    
    while(!isEmpty(&r) || start){
        while(dir<8){   //嘗試不同方向
            //以現在位置(tr,tc)為中心，嘗試走走看周邊8格
            nextr = tr + move[dir].rdir;
            nextc = tc + move[dir].cdir;

            // 若「下一步」在標記上沒走過(=0) 且 地圖上也可以走(=0)
            // 則將「現在位置 & 往下一步的方向」Push到Stack
            // 之後標記此步(=6)，「往前走(將 合法的下步位置 寫入 現在位置)」
            if(!m[nextr][nextc] && !mz[nextr][nextc]){
                newItem.r=tr; newItem.c=tc; newItem.dir=dir;
                Push(&r,newItem);
                m[nextr][nextc] = 6;
                tr=nextr; tc=nextc;
                dir=2;  //初始化行走方向(E)
                start=0;//確保 Stack有資料，即可關閉旗標
                
                //若抵達終點，則 Push 現在位置，並印出整個Stack
                if((tr==MazeH)&&(tc==MazeW)){
                    newItem.r=tr; newItem.c=tc; newItem.dir=2;
                    Push(&r,newItem);
                    printPath(&r);
                    return;
                }
            }
            //若「下一步」不能走，則嘗試其他方向
            //其中，出口在最SE方位，故從E、S開始試較佳
            //2,4,6,0 -> 3,5,7,1
            else { 
                switch(dir){
                    case 0: dir=3; break;
                    case 1: dir=8; break;
                    case 2: dir=4; break;
                    case 3: dir=5; break;
                    case 4: dir=6; break;
                    case 5: dir=7; break;
                    case 6: dir=0; break;
                    case 7: dir=1; break;
                }
            }
        }
        // 若8個方位都走不通 -> 退回上一步
        // 將 現在位置 標記為「死路(4)」，再Pop出上一步的位置，將其 寫入 現在位置
        m[tr][tc] = 4;
        Pop(&r,&popItem);
        tr = popItem.r; tc = popItem.c;
        dir = 2;    //初始化行走方向(E)
    }
}
