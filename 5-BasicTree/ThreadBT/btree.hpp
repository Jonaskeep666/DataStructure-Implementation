#ifndef _BTREE_H_
#define _BTREE_H_

#include <iostream>
#include "queue.hpp"
#include "stack.hpp"
using namespace std;

template <class T> class Tree;

template <class T>
class TreeNode{
    friend class Tree<T>;
    public:
        TreeNode(){
            rightThread = leftThread = false;
            leftChild = rightChild = 0;
        }
        TreeNode(T d){
            data = d;
            rightThread = leftThread = false;
            leftChild = rightChild = 0;
        }
    private:
        T data;
        bool rightThread,leftThread;
        TreeNode *leftChild;
        TreeNode *rightChild;
};

template <class T>
class Tree{
    public:
        Tree(){root = 0;}
        ~Tree();

        bool isEmpty(){return root == 0;}

        //Traversal
        void visit(TreeNode<T> *current);
        void inorder(){inorder(root);}
        void inorder(TreeNode<T> *current);
        void preorder(){preorder(root);}
        void preorder(TreeNode<T> *current);
        void postorder(){postorder(root);}
        void postorder(TreeNode<T> *current);
        void levelorder(){levelorder(root);}
        void levelorder(TreeNode<T> *current);

        //Access
        TreeNode<T>* getAddr(int index);
        T getData(int index);
        T getData(TreeNode<T> *current) {return current->data;}
        void insert(int index,char dir,T d);

        //Thread operate 
        TreeNode<T>* InorderSucc(TreeNode<T> *current);
        TreeNode<T>* InorderPredec(TreeNode<T> *current);
        void inorderThread();

    private:
        TreeNode<T> *root;
};

//******* Destructor *******
template <class T>
Tree<T>::~Tree(){
    TreeNode<T> *delNode, *current;
    Stack< TreeNode<T>* > s(10);

    current = root->leftChild;
    s.Push(root);

    while(1){
        while(current && s.Top() != current){
            s.Push(current);
            current = current->leftChild;
            // cout<<"L("<<current<<"),"<<endl;
        }
        current = s.Top();
        if(!current->leftChild && !current->rightChild){
            if(current == root){ delete root; root = 0; break;}

            s.Pop(delNode);
            current = s.Top();
            if(current->leftChild == delNode) current->leftChild = 0;
            else if(current->rightChild == delNode) current->rightChild = 0;
            delete delNode;
        }
        else{
            current = current->rightChild;
        }
    }
}


//******* Traversal *******
template <class T>
void Tree<T>::visit(TreeNode<T> *current){
    cout << "[" <<current->data << "],";
}

template <class T>
void Tree<T>::inorder(TreeNode<T> *current){
    if(current){
        if(!current->leftThread) inorder(current->leftChild);
        visit(current);
        if(!current->rightThread) inorder(current->rightChild);
    }
}
template <class T>
void Tree<T>::preorder(TreeNode<T> *current){
    if(current){
        visit(current);
        if(!current->leftThread) preorder(current->leftChild);
        if(!current->rightThread) preorder(current->rightChild);
    }
}
template <class T>
void Tree<T>::postorder(TreeNode<T> *current){
    if(current){
        if(!current->leftThread) postorder(current->leftChild);
        if(!current->rightThread) postorder(current->rightChild);
        visit(current);
    }
}
template <class T>
void Tree<T>::levelorder(TreeNode<T> *current){
    if(current){
        Queue< TreeNode<T>* > q(10);
        while(current){
            visit(current);
            if(!current->leftThread) q.Push(current->leftChild);
            if(!current->rightThread) q.Push(current->rightChild);
            if(q.isEmpty()) return;
            q.Pop(current);
        } 
    }
}

//******* Access *******
template <class T>
TreeNode<T>* Tree<T>::getAddr(int index){
    TreeNode<T>* current = root;
    int count = 1;
    if(current){
        Queue< TreeNode<T>* > q(10);
        while(count != index){
            if(!current->leftThread) q.Push(current->leftChild);
            if(!current->rightThread) q.Push(current->rightChild);
            if(q.isEmpty()) break;
            q.Pop(current);
            count++;
        } 
        return current;
    }
    else{
        cout << "Tree is Empty!" << endl;
        return 0;
    }
}

template <class T>
T Tree<T>::getData(int index){
    TreeNode<T> *current = getAddr(index);
    return current->data;
}

template <class T>
void Tree<T>::insert(int index,char dir,T d){
    TreeNode<T> *r = getAddr(index);
    TreeNode<T> *newNode = new TreeNode<T>(d);
    TreeNode<T> *temp = 0;

    if(index == 1 && !r){
        root = r = newNode;
        root->leftThread = root->rightThread = true;
    }
    else if(r){
        if(dir=='L'){
            newNode->leftThread = r->leftThread;
            newNode->leftChild = r->leftChild;
            newNode->rightThread = true;
            newNode->rightChild = r;
            r->leftThread = false;
            r->leftChild = newNode;
            if(!newNode->leftThread){
                temp = InorderPredec(r);
                temp->leftChild = newNode;
            }
        }
        else if(dir=='R'){
            newNode->rightThread = r->rightThread;
            newNode->rightChild = r->rightChild;
            newNode->leftThread = true;
            newNode->leftChild = r;
            r->rightThread = false;
            r->rightChild = newNode;
            if(!newNode->rightThread){
                temp = InorderSucc(r);
                temp->leftChild = newNode;
            }
        }
    }
    else cout << "The node isn't exist.";
}

//******* Thread operate *******
template <class T>
TreeNode<T>* Tree<T>::InorderSucc(TreeNode<T> *current){
    if(current->rightThread) {
        return current->rightChild;
    }
    else{
        current = current->rightChild;
        while(!current->leftThread){
            current = current->leftChild;
        }
        return current;
    }
}

template <class T>
TreeNode<T>* Tree<T>::InorderPredec(TreeNode<T> *current){
    if(current->leftThread) {
        return current->leftChild;
    }
    else{
        current = current->leftChild;
        while(!current->rightThread){
            current = current->rightChild;
        }
        return current;
    }
}

template <class T>
void Tree<T>::inorderThread(){
    TreeNode<T>* current = root;
    //先衝到最左邊
    while(current->leftChild)   //最左邊，左指標指向「0」
        current = current->leftChild;
    //根據Thread 進行Inorder走訪
    while(current->rightChild){  //最右邊，右指標指向「0」
        visit(current);
        current = InorderSucc(current);
    }
    visit(current);
    return;
}

#endif
