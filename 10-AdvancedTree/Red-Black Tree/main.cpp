#include <iostream>
#include "redblack.hpp"
using namespace std;

int main(){
    int num1[10] = {2,5,8,4,3,1,9,10,7,6};
    int num2[] = {36,16,41,4,22,39,48,3,9,19,27,45,52,1,7,10,24,51,55};

    RBTree RBt;

    // RBt.insertNode(50);
    // RBt.insertNode(10);
    // RBt.insertNode(80);
    // RBt.insertNode(90);

    // RBt.insertNode(70);
    // RBt.insertNode(60);

    // RBt.insertNode(65);
    // RBt.insertNode(62);

    for(int i=0;i<(int)sizeof(num2)/sizeof(int);++i){
        RBt.insertNode(num2[i]);
    }

    // RBt.buildTree();


    RBt.printRBTree();
    cout << endl;

    cout<< (int)sizeof(num2)/sizeof(int) <<endl;
    cout << RBt.count(0) <<endl;
    cout << RBt.count(1) <<endl;

    // RBt.deleteNode(22);


    // RBt.printRBTree();
    // cout << endl;

    // RBt.deleteNode(5); 

    // RBt.printRBTree();
    // cout << endl;

    // RBt.deleteNode(6); 

    // RBt.printRBTree();
    // cout << endl;

}
