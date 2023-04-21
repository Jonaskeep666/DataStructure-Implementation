#include <iostream>
#include "avl.hpp"
using namespace std;

int main(){
    int num[10] = {2,5,8,4,3,1,9,10,7,6};
    AVLtree avl;

    // avl.insertNode(2);
    // avl.insertNode(5);
    // avl.insertNode(8);

    for(int i=0;i<10;++i){
        avl.insertR(num[i]);
    }

    avl.printAVLtree();
    cout << endl;

    avl.deleteNode(5); 

    avl.printAVLtree();
    cout << endl;

    avl.deleteNode(6); 

    avl.printAVLtree();
    cout << endl;

}
