#include <iostream>
#include "bst.hpp"
using namespace std;

int main(){
    int num[10] = {3,19,6,7,31,13,94,38,52,48};
    Data<int> input[10];

    BSTree<int> bst;

    for(int i=0;i<10;++i){
        input[i].setData(num[i],num[i]);
        cout << input[i] << ",";
    }
    cout << endl;

    for(int i=0;i<10;++i){
        bst.insert(input[i]);
    }
    
    cout << endl;
    bst.inorder();
    cout << endl;
    bst.postorder();
    cout << endl;
    bst.preorder();
    cout << endl;
    bst.levelorder();
    cout << endl;

    Data<int> test={6,6};

    // char c='0',p='P';
    // BstNode<int>* current = bst.searchKey(c,test);
    // BstNode<int>* parent = bst.searchKey(p,test);

    // cout << bst.getData(current) << endl;
    // cout << bst.getData(parent) << endl;
    
    bst.deleteNode(test);
    cout << endl;
    bst.inorder();
    cout << endl;
}
