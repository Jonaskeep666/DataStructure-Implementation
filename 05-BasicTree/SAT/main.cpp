#include <iostream>
#include "btree.hpp"
using namespace std;


int main(){
    Tree<char> tree;
    char x[3]={'0','0','0'};

    for(int i=0;i<8;++i){
        x[0]=(i/(2*2))+48;
        x[1]=((i%(2*2))/2)+48;
        x[2]=((i%2))+48;

        cout << x[0] <<","<< x[1] <<","<< x[2] << endl;

        tree.insert(1,'F','+');
        tree.insert(1,'L','+');
        tree.insert(1,'R','~');
        tree.insert(2,'L','*');
        tree.insert(2,'R','*');
        tree.insert(3,'R',x[2]);
        tree.insert(4,'L',x[0]);
        tree.insert(4,'R','~');
        tree.insert(5,'L','~');
        tree.insert(5,'R',x[2]);
        tree.insert(8,'R',x[1]);
        tree.insert(9,'R',x[0]);

        tree.inorder();
        cout << endl;

        cout <<"SAT="<< tree.PostOrderEval()<<endl;
        cout <<"----------------------------------"<<endl;

        tree.~Tree();
    }
}
