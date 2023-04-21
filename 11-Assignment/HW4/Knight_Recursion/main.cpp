#include <iostream>
#include "stack.h"
#include "stack.cpp"
using namespace std;

class Pos{
    friend Pos operator+(Pos &a, Pos &b);
    friend ostream& operator<<(ostream& os, Pos &a);
    public:
        void setPos(int r_, int c_){
            r=r_; c=c_; d=0;
        }
        void setDir(int dir){ d = dir;}
        int row(){ return r;}
        int col(){ return c;}
        int dir(){ return d;}
        Pos go(int i){
            Pos next; next.setPos(0,0); next.setDir(i);
            switch(i){
                case 1: next.r = r - 2; next.c = c + 1;
                    return next; break;
                case 2: next.r = r - 1; next.c = c + 2;
                    return next; break;
                case 3: next.r = r + 1; next.c = c + 2;
                    return next; break;
                case 4: next.r = r + 2; next.c = c + 1;
                    return next; break;
                case 5: next.r = r + 2; next.c = c - 1;
                    return next; break;
                case 6: next.r = r + 1; next.c = c - 2;
                    return next; break;
                case 7: next.r = r - 1; next.c = c - 2;
                    return next; break;
                case 8: next.r = r - 2; next.c = c - 1;
                    return next; break;
                default:next.r = r; next.c = c;
                    return next; break;
            }
        }
    private:
        int r;
        int c;
        int d;
};
Pos operator+(Pos &a, Pos &b){
    Pos c;
    c.r = a.r + b.r;
    c.c = a.c + b.c;
    c.d = a.d;
    return c;
}
ostream& operator<<(ostream& os, Pos &a){
    os << "(" << a.r << "," << a.c <<")";
    os << "[" << a.d << "]" << endl;
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


/*
演算法概述：
1>	終止條件
	(1)	當count == n*n -> fsol=1、印出「解=Map」
	(2)	當「現在位置=(1,1)」&& dir>8 -> 印出「無解」
	(3)	當fsol=1時，會 跳過 遞迴求解的步驟

2>	當fsol≠1時
	-> 以 now 為中心，從dir=1開始嘗試不同方向的下一步
	(1)	若下一步「合法」
		-> 標記下一步的步數(+1) -> (改變狀態)
		-> 進入「下一步」-> (走向「下一層」)
		-> 從「下一步」退回，代表此路不通 -> 取消標記、步數-1 -> (回復狀態)

	(2)	若下一步「不合法」or 從「上一步退回」
		-> 則繼續嘗試下一個方向 (dir++)

	(3)	若8個方向都不合法，且已經退回到 起始位置(1,1) -> 終止條件(2)
*/

void path(int n, int count,Pos &now, Map& m, int& fsol){
    Pos next;
    int dir=1;

    if(count == n*n){
        fsol=1;
        cout << "n=" << n <<":" << endl;
        cout << m;
        return;
    }
    else if(!fsol) {
        while(dir<9 && !fsol){
            next = now.go(dir);
            if(m.isElement(next.row(),next.col(),0)){
                m.setElement(next.row(),next.col(),++count);
                path(n, count, next, m, fsol);
                m.setElement(next.row(),next.col(),0);
                count--;
            }
            dir++;
        }
        if(now.row()==1 && now.col()==1 && dir>8){
            fsol=1;
            cout << "n=" << n <<":" << endl;
            cout << "No solution!\n" << endl;
        }
    }
}

int main(void){
    Pos now;
    int fsol;   // 判斷是否繼續求解的旗標

    for(int i=1;i<8;++i){
        now.setPos(1,1);    // 初始化現在位置
        Map m(i);           // 宣告標記地圖
        m.setElement(now.row(),now.col(),1); //標記起始位置
        fsol=0;             // 尚未找到解
        path(i,1,now,m,fsol);
    }
}
