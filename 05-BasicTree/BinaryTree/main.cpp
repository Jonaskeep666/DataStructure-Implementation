#include <iostream>
#include "btree.hpp"
using namespace std;

int main(){
    Tree<int> tree, treecat;

   

    // tree.insert(1,'F','+');
    // tree.insert(1,'L','*');
    // tree.insert(1,'R','E');
    // tree.insert(2,'L','*');
    // tree.insert(2,'R','D');
    // tree.insert(4,'L','/');
    // tree.insert(4,'R','C');
    // tree.insert(6,'L','A');
    // tree.insert(6,'R','B');

    tree.insert(1,'F',1);
    tree.insert(1,'L',2);
    tree.insert(1,'R',3);
    tree.insert(2,'L',4);
    tree.insert(2,'R',5);
    tree.insert(3,'L',6);
    tree.insert(3,'R',7);
    tree.insert(4,'R',8);
    tree.insert(6,'R',9);
    tree.insert(8,'L',10);
    tree.insert(10,'R',11);
    tree.insert(11,'L',12);
    tree.insert(11,'R',13);
    tree.insert(13,'R',14);
    tree.insert(14,'R',15);

    cout<<endl;
    tree.inorder();
    cout<<endl;
    tree.preorder();
    cout<<endl;
    tree.postorder();
    cout<<endl;
    cout<<endl;
    tree.levelorder();
    cout<<endl;

    cout << tree.isEmpty() << endl;
    tree.~Tree();
    cout << tree.isEmpty() << endl;
    

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
