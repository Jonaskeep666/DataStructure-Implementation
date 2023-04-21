#ifndef _BST_H_
#define _BST_H_

#include <iostream>
#include "queue.hpp"
#include "stack.hpp"
using namespace std;

template <class T> class BSTree;

template <class T>
struct Data{
    int key;
    // T element;
    void setData(int k){
        key = k;
    }
};
template <class T>
ostream& operator<<(ostream& os, Data<T> d){
    os << "" << d.key << "";
    return os;
}

template <class T>
class BstNode{
    friend class BSTree<T>;
    public:
        BstNode(){leftChild = rightChild = 0;}
        BstNode(Data<T> d){
            data = d;
            leftChild = rightChild = 0;
        }
    private:
        Data<T> data;
        BstNode *leftChild;
        BstNode *rightChild;
};

template <class T> ostream& operator<< (ostream& os, BSTree<T> bst);

template <class T>
class BSTree{
    friend ostream& operator<< <T>(ostream& os, BSTree bst);

    public:
        BSTree(){root = 0; size=0;}
        ~BSTree();
        void destroyRecursive(BstNode<T>* r);

        bool isEmpty(){return root == 0;}
        int getSize(){return size;}

        //Traversal
        void visit(BstNode<T> *current);
        void inorder(){inorder(root);}
        void inorder(BstNode<T> *current);
        void preorder(){preorder(root);}
        void preorder(BstNode<T> *current);
        void postorder(){postorder(root);}
        void postorder(BstNode<T> *current);
        void levelorder(){levelorder(root);}
        void levelorder(BstNode<T> *current);

        //印出BST
        void printBST(){printBST(root);}
        void printBST(BstNode<T> *current);

        //Access
        BstNode<T>* getAddr(int index);
        Data<T> getData(int index);
        Data<T> getData(BstNode<T>* r){return r->data;}
        void insert(int index,char dir,Data<T> d);

        //BST
        void insert(Data<T> d);
        BstNode<T>* searchKey(char& c, Data<T> d);
        void deleteNode(Data<T> d);

    private:
        BstNode<T> *root;
        int size;
};

template <class T>
ostream& operator<< (ostream& os, BSTree<T> bst){
    os << endl;
    bst.printBST();
    os << endl;
    return os;
}

//******* Destructor *******
// template <class T>
// Tree<T>::~Tree(){
//     BstNode<T> *delNode, *current;
//     Stack< BstNode<T>* > s(10);

//     current = root->leftChild;
//     s.Push(root);

//     while(1){
//         while(current && s.Top() != current){
//             s.Push(current);
//             current = current->leftChild;
//             // cout<<"L("<<current<<"),"<<endl;
//         }
//         current = s.Top();
//         if(!current->leftChild && !current->rightChild){
//             if(current == root){ delete root; root = 0; break;}

//             s.Pop(delNode);
//             current = s.Top();
//             if(current->leftChild == delNode) current->leftChild = 0;
//             else if(current->rightChild == delNode) current->rightChild = 0;
//             delete delNode;
//         }
//         else{
//             current = current->rightChild;
//         }
//     }
// }

template <class T>
BSTree<T>::~BSTree(){
    destroyRecursive(root);
    root = 0;
}
template <class T>
void BSTree<T>::destroyRecursive(BstNode<T>* r){
    if(r){
        destroyRecursive(r->leftChild);
        destroyRecursive(r->rightChild);
        delete r;
    }
}


//******* Traversal *******
template <class T>
void BSTree<T>::visit(BstNode<T> *current){
    cout << "[" <<current->data << "]\t";
}

template <class T>
void BSTree<T>::inorder(BstNode<T> *current){
    if(current){
        inorder(current->leftChild);
        visit(current);
        inorder(current->rightChild);
    }
}
template <class T>
void BSTree<T>::preorder(BstNode<T> *current){
    if(current){
        visit(current);
        preorder(current->leftChild);
        preorder(current->rightChild);
    }
}
template <class T>
void BSTree<T>::postorder(BstNode<T> *current){
    if(current){
        postorder(current->leftChild);
        postorder(current->rightChild);
        visit(current);
    }
}
template <class T>
void BSTree<T>::levelorder(BstNode<T> *current){
    if(current){
        Queue< BstNode<T>* > q(10);
        while(current){
            visit(current);
            if(current->leftChild) q.Push(current->leftChild);
            if(current->rightChild) q.Push(current->rightChild);
            if(q.isEmpty()) return;
            q.Pop(current);
        } 
    }
}

template <class T>
void BSTree<T>::printBST(BstNode<T> *current){
    Stack< BstNode<T>* > s(2*size);
    Queue< Data<T> > qlChild(2*size);
    Queue< Data<T> > qrChild(2*size);
    Data<T> temp={0};

    cout << "Node:\t";
    while(1){
        //Phase 1: 衝到最左邊
        while(current){
            s.Push(current);
            current = current->leftChild;
        }
        //Phase 2: 印出 往右走
        if(!s.isEmpty()){
            s.Pop(current);
            visit(current);
            if(current->leftChild)
                qlChild.Push(current->leftChild->data);
            else qlChild.Push(temp);
            if(current->rightChild)
                qrChild.Push(current->rightChild->data);
            else qrChild.Push(temp);
            current = current->rightChild;
        }
        else break;
    }
    cout << "\nLeft:\t";
    while(!qlChild.isEmpty()){
        qlChild.Pop(temp);
        cout << "[" << temp << "]\t";
    }
    cout << "\nRight:\t";
    while(!qrChild.isEmpty()){
        qrChild.Pop(temp);
        cout << "[" << temp << "]\t";
    }
}


//******* Access *******
template <class T>
BstNode<T>* BSTree<T>::getAddr(int index){
    BstNode<T>* current = root;
    int count = 1;
    if(current){
        Queue< BstNode<T>* > q(10);
        while(count != index){
            if(current->leftChild) q.Push(current->leftChild);
            if(current->rightChild) q.Push(current->rightChild);
            if(q.isEmpty()) break;
            q.Pop(current);
            count++;
        } 
        return current;
    }
    else{
        cout << "BSTree is Empty!" << endl;
        return 0;
    }
}

template <class T>
Data<T> BSTree<T>::getData(int index){
    BstNode<T> *current = getAddr(index);
    return current->data;
}

template <class T>
void BSTree<T>::insert(int index,char dir,Data<T> d){
    BstNode<T> *r = getAddr(index);
    BstNode<T> *newNode = new BstNode<T>(d);
    
    if(index == 1 && !r) root = r = newNode;
    else if(r){
        if(dir=='L'){
            newNode->leftChild = r->leftChild;
            r->leftChild = newNode;
        }
        else if(dir=='R'){
            newNode->leftChild = r->rightChild;
            r->rightChild = newNode;
        }
        size++;
    }
    else cout << "The node isn't exist.";
}


// BST insert & searchKey
template <class T>
void BSTree<T>::insert(Data<T> d){
    BstNode<T> *current;
    BstNode<T> *newNode = new BstNode<T>(d);
    char c='0';
    if(!root) root = newNode;
    else{
        current = searchKey(c,d);
        switch (c){
            case 'S': cout << "The node exists." <<endl; 
                return;
                break;
            case 'L': current->leftChild = newNode;
                break;
            case 'R': current->rightChild = newNode;
                break;
        }
    }
    size++;
}
template <class T>
BstNode<T>* BSTree<T>::searchKey(char& c,Data<T> d){
    BstNode<T> *current = root;
    BstNode<T> *parent = root;

    while(current){
        if(d.key > current->data.key){
            if(current->rightChild){
                parent = current;
                current = current->rightChild;
            } 
            else {
                c='R';  break;
            } 
        }
        else if(d.key < current->data.key) {
            if(current->leftChild){
                parent = current;
                current = current->leftChild;
            } 
            else {
                c='L';  break;
            } 
        }
        else if(d.key == current->data.key) {  
            //新增功能 for deleteNode
            //當控制旗標='P'，則回傳current的Parent
            if(c =='P') return parent;  
            c = 'S';
            break;
        }   
    }
    return current;
}

// BST Delete

template <class T>
void BSTree<T>::deleteNode(Data<T> d){
    char c='0',p='P';
    BstNode<T>* current = searchKey(c,d);
    BstNode<T>* parent = searchKey(p,d);
    
    if(c!='S'){ cout << "The node doesn't exist." << endl; return;}
    //Case 1 current = leaf(無孩)
    if(!current->leftChild && !current->rightChild){
        //當current 為 root時（會有 parent = current) -> 直接令root指向NULL
        if(parent == current){ 
            root = 0; 
        }
        //否則 將 父點指向current的指標 指向NULL
        else{
            if(parent->leftChild == current) parent->leftChild=0;
            else parent->rightChild = 0;
        }
        delete current; //刪掉current
    }
    //Case 3 current = D2 Node(2孩)
    else if(current->leftChild && current->rightChild){
        BstNode<T>* swapchild = current->leftChild; //指向要交換的「左樹最大者」
        BstNode<T>* swapparent = current;           //指向「左樹最大者的老爸」
        //找「左樹最大者」就是在左子樹中 往右邊衝到底(swapchild->rightChild=0為止)
        while(swapchild->rightChild){
            swapparent = swapchild;
            swapchild = swapchild->rightChild;
        }
        current->data = swapchild->data;    //將「左樹最大者」data 存入 current
        swapparent->rightChild = 0;         //再將「左樹最大者的老爸」指向孩子的指標清掉
        delete swapchild;                   //最後刪除該Node
    }
    //Case 2 current = D1 Node(1孩)
    else if(current->leftChild && !current->rightChild){    //只有左孩
        //當current 為 root時，root 指向 左孩
        if(parent == current) {
            root = current->leftChild;
        }
        //否則 將 父點指向current的指標 指向 current的孩子
        else{
            if(parent->leftChild == current) parent->leftChild = current->leftChild;
            else parent->rightChild = current->leftChild;
        }
        delete current; //刪掉current
    }
    else if(!current->leftChild && current->rightChild){    //只有右孩
        if(parent == current) {
            root = current->rightChild;
        }
        else{
            if(parent->leftChild == current) parent->leftChild = current->rightChild;
            else parent->rightChild = current->rightChild;
        }
        delete current;
    }
    size--;
}



#endif
