#include <iostream>
#include "btree.hpp"
using namespace std;

int main(){
    Tree<char> tree, treecat;

   

    tree.insert(1,'F','A');
    tree.insert(1,'L','B');
    tree.insert(1,'R','C');
    tree.insert(2,'L','D');
    tree.insert(2,'R','E');
    tree.insert(3,'L','F');
    tree.insert(3,'R','G');
    tree.insert(4,'L','H');
    tree.insert(4,'R','I');


    cout << tree.getData(tree.InorderPredec(tree.getAddr(5))) << endl;
    cout << tree.getData(tree.InorderSucc(tree.getAddr(5))) <<endl;
    cout << tree.getData(tree.InorderPredec(tree.getAddr(2))) << endl;
    cout << tree.getData(tree.InorderSucc(tree.getAddr(2))) <<endl;

    // tree.insert(1,'F',1);
    // tree.insert(1,'L',2);
    // tree.insert(1,'R',3);
    // tree.insert(2,'L',4);
    // tree.insert(2,'R',5);
    // tree.insert(3,'L',6);
    // tree.insert(3,'R',7);
    // tree.insert(4,'R',8);
    // tree.insert(6,'R',9);
    // tree.insert(8,'L',10);
    // tree.insert(10,'R',11);
    // tree.insert(11,'L',12);
    // tree.insert(11,'R',13);
    // tree.insert(13,'R',14);
    // tree.insert(14,'R',15);

    cout<< "Start here" <<endl;
    // cout << tree.getAddr(1) <<endl;
    tree.inorder();
    cout<<endl;
    tree.preorder();
    cout<<endl;
    tree.postorder();
    cout<<endl;
    cout<<endl;
    tree.levelorder();
    cout<<endl;

    tree.inorderThread();
    cout<<endl;


    // cout << tree.isEmpty() << endl;
    // tree.~Tree();
    // cout << tree.isEmpty() << endl;
    

    // cout<< tree.equalTree(tree,treecat) <<endl;
    // treecat.copyTree(tree);
    // cout<< tree.equalTree(tree,treecat) <<endl;
    
    // cout<<endl;
    // treecat.inorder();
    // cout<<endl;
    // treecat.preorder();
    // cout<<endl;
    // treecat.postorder();
    // cout<<endl;
    // cout<<endl;
    // treecat.levelorder();
    // cout<<endl;

    
}
