#include <iostream>
#include <cmath>
#include "match.h"
using namespace std;

int main(void){
    string s="abcabcabcabe";
    string p="abcabe";

    int idx = indexKMP(s,p);

    for(int i=idx;i<(idx+p.size());++i)
        cout << s[i] << ",";
    cout << endl;
}





// class Position {
//     public:
//         Position(int x_, int y_){
//             x=x_; y=y_;
//         }
//         int getPos();         //Getter
//         void setPos(int,int); //Setter

//         friend class Line;

//     private:
//         int x,y;
// };

// class Line {
//     public:
//         double lineLength(Position& a,Position& b){
//             return sqrt((double)((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)));
//         }
// };

// int main(void){
//     Position p1(1,2),p2(3,5);
//     Line line1;
//     cout << line1.lineLength(p1,p2);
// }

