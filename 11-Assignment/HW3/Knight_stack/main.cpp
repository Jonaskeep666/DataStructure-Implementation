#include <iostream>
#include "stack.h"
#include "stack.cpp"
using namespace std;

class Pos{
    friend Pos operator+(Pos &a, Pos &b);
    friend ostream& operator<<(ostream& os, Pos &a);
    public:
        void setPos(int r_, int c_){
            r=r_; c=c_; dir=0;
        }
        void setDir(int dir_){ dir = dir_;}
        int row(){ return r;}
        int col(){ return c;}
        int direction(){ return dir;}
    private:
        int r;
        int c;
        int dir;
};
Pos operator+(Pos &a, Pos &b){
    Pos c;
    c.r = a.r + b.r;
    c.c = a.c + b.c;
    c.dir = a.dir;
    return c;
}
ostream& operator<<(ostream& os, Pos &a){
    os << "(" << a.r << "," << a.c <<")";
    os << "[" << a.dir << "]" << endl;
    return os;
}

class Map{
    friend ostream& operator<<(ostream& os, Map &m);
    public:
        Map(int n_){
            n=n_;
            map = new int*[n+4];
            for(int i=0;i<(n+4);++i){
                *(map+i) = new int[n+4];
                for(int j=0;j<(n+4);++j)
                    map[i][j]=0;
            }
            for(int i=0;i<(n+4);++i){
                map[0][i]=1;    map[1][i]=1;
                map[n+2][i]=1;  map[n+3][i]=1;
                map[i][0]=1;    map[i][1]=1;
                map[i][n+2]=1;  map[i][n+3]=1;
            }
        }
        bool isElement(int r,int c,int e){
            return (map[r+1][c+1]==e)?true:false;
        }
        void setElement(int r,int c,int e){ map[r+1][c+1]=e; }
    private:
        int **map;
        int n;
};
ostream& operator<<(ostream& os, Map &m){
    for(int i=2;i<(m.n+2);++i){
        for(int j=2;j<(m.n+2);++j)
            os << m.map[i][j] << "\t";
        os << endl;
        os << endl;
    }
    return os;
}

void initialMove(Pos* move){
    move[1].setPos(-2,1);
    move[2].setPos(-1,2);
    move[3].setPos(1,2);
    move[4].setPos(2,1);
    move[5].setPos(2,-1);
    move[6].setPos(1,-2);
    move[7].setPos(-1,-2);
    move[8].setPos(-2,-1);
}

void printRecord(Stack<Pos> &s){
    Pos popItem;
    while(!s.isEmpty()){
        s.Pop(popItem);
        cout << popItem;
    }
}

/*
演算法概述：
1>  以「現在位置」為中心，嘗試「8個不同方向」的下一步
2>  若下一步「合法(=0)」-> Push 現在位置 & 嘗試的方向d (存入Stack)
    -> 再將下一步位置 存入 現在位置，並「紀錄步數」
    (1) 此時，若「嘗試步數 == n*n」-> 「達到目標」，印出 Map
    (2) 此時，若「尚未達到目標」
        -> 初始化下一步的嘗試方向，並將 嘗試步數+1
3>  若下一步「不合法(≠0)」-> 換下一個方向 d++
4>  若以「現在位置」為中心，8個方位的下一步都不合法(d>8) 
    -> 「退後一步」
    (1) 將「現在位置」標記為沒走過(=0)，並將 嘗試步數-1
    (2) Pop 上一步位置、方向，將其 寫入「現在位置」
        -> 並嘗試 新方向 d+1 
    (3) 若新方向 d>8，則「再退一步」，直到 d<8

5>  若「現在位置」退回到「初始位置(x,y)」
    -> 且所有方向都嘗試過(d>8) -> 「無解」
*/

void path(int n,int x,int y){
    Stack<Pos> record(100);
    Map m(n);

    Pos move[9];
    initialMove(move);

    Pos now,next;  now.setPos(x,y); //初始化現在位置
    int d=1;        //初始化嘗試方向
    int count=1;    //初始化步數紀錄
    m.setElement(now.row(),now.col(),count++);  //標記第一步

    // For n=1
    if(n==1){ cout << m; return; }

    while(1){
        while(d<9){
            //以「現在位置」為中心，嘗試下一步(方向d)
            next = now + move[d];
            
            // 若下一步「合法(=0)」-> Push 現在位置 & 嘗試的方向d
            // -> 將下一步位置 存入 現在位置，並「紀錄步數」
            // -> 初始化下一步的嘗試方向，並將 嘗試步數+1
            if(m.isElement(next.row(),next.col(),0)){
                now.setDir(d);
                record.Push(now);
                now = next;
                m.setElement(now.row(),now.col(),count);
                
                // 當「嘗試步數 == n*n」-> 「達到目標」，印出 Map
                if(count == (n*n)){
                    //printRecord(record);
                    cout << m << endl;
                    return; //「達到目標」-- return 1
                }
                
                d=1;
                count++;
            }
            // 若下一步「不合法(≠0)」-> 換下一個方向 d++
            else d++;

            // 若「現在位置」回到「初始位置(x,y)」
            // 且所有的方向都嘗試過(d>8) -> 「無解」
            if((now.row()==x) && (now.col()==y) && d>8){
                cout << "No solution!\n" << endl;
                return; //「無解」-- return 2
            }
        }
        
        // 若以「現在位置」為中心，8個方位的下一步都不合法(d>8) -> 「退後一步」
        // -> 將「現在位置」標記為沒走過(=0)，並將 嘗試步數-1
        // -> Pop 上一步位置、方向d，再將其 寫入「現在位置」
        // -> 並嘗試 新方向 d+1 
        // -> 若新方向 d>8，則「再退一步」
        while(d>8){
            m.setElement(now.row(),now.col(),0);
            count--;
            record.Pop(now);
            d = now.direction() + 1;
        }
    } 
}

int main(void){
    for(int i=1;i<8;++i){
        cout << "n=" << i << ":" << endl;
        path(i,1,1);
    }
}
