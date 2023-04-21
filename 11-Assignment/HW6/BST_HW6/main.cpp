#include <iostream>
#include "bst.hpp"
using namespace std;

void checkBSTree(Data<int> input,BSTree<int> &bst){
    char c='0';
    bst.searchKey(c,input);
    if(c=='S') bst.deleteNode(input);
    else bst.insert(input);
}

int main(){
    BSTree<int> bstree[2];
    int t=0;
    int inputData=0;
    Data<int> inputData_;
    //  當 cin 讀到 EOF 時 則跳出迴圈
    //  EOF 在 Windows是Ctrl+Z & macOS/Linux是Ctrl+D
    while(cin >> inputData){
        while(inputData!=-1){
            inputData_.setData(inputData);
            checkBSTree(inputData_,bstree[t]);
            cin >> inputData;
        }
        t++;
    }

    for(int i=0;i<2;i++){
        cout << bstree[i];
    }


    // // int num[10] = {3,19,6,7,31,13,94,38,52,48};
    // int num1[10] = {10,7,12,8,11,4};
    // Data<int> input[10];

    // BSTree<int> bst;

    // for(int i=0;i<10;++i){
    //     input[i].setData(num1[i]);
    //     cout << input[i] << ",";
    // }
    // cout << endl;

    // for(int i=0;i<6;++i){
    //     bst.insert(input[i]);
    // }

    // cout << bst.getSize()<<endl;
    
    // // cout << endl;
    // // bst.inorder();
    // // cout << endl;
    // // bst.postorder();
    // cout << "Preorder" <<endl;
    // bst.preorder();
    // cout << endl;
    // // bst.levelorder();
    // // cout << endl;

    // cout << bst;

    // // Data<int> test={6,6};

    // // char c='0',p='P';
    // // BstNode<int>* current = bst.searchKey(c,test);
    // // BstNode<int>* parent = bst.searchKey(p,test);

    // // cout << bst.getData(current) << endl;
    // // cout << bst.getData(parent) << endl;
    
    // // bst.deleteNode(test);
    // // cout << endl;
    // // bst.inorder();
    // // cout << endl;
}
