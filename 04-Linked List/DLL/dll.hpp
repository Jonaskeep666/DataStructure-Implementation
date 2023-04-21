#ifndef _DLL_H_
#define _DLL_H_

#include <iostream>
using namespace std;

template <class T>
class DLList;
template <class T>
ostream& operator<<(ostream& os,DLList<T>& dll);

template <class T>
class DLLNode{
    friend class DLList<T>;
    friend ostream& operator<< <T>(ostream& os,DLList<T>& dll);

    public:
        DLLNode(){left = right = this;}
        DLLNode(T d){
            data = d; 
            left = right = this;
        }
    private:
        T data;
        DLLNode* left;
        DLLNode* right;
};

template <class T>
class DLList{
    friend ostream& operator<< <T>(ostream& os,DLList<T>& dll);

    public:
        DLList(){
            headNode = new DLLNode<T>();
            size=0;
        }
        bool isEmpty(){ return headNode->right == headNode;}
        int getSize(){ return size; } 
        
        //Traversal
        DLLNode<T>* getAddr(int index);
        //Access
        T getAt(int index);
        void insertAfter(int index, T element);
        void deleteNode(int index);
    private:
        DLLNode<T> *headNode;
        int size;
};

template <class T>
DLLNode<T>* DLList<T>::getAddr(int index){
    DLLNode<T> *current = headNode;
    if(index > (size/2))
        for(int i=(size+1);i>index;--i)
            current = current->left;
    else
        for(int i=0;i<index;++i)
            current = current->right;
    return current;
}

template <class T>
T DLList<T>::getAt(int index){
    DLLNode<T> *current = getAddr(index);
    return current->data;
}

template <class T>
void DLList<T>::insertAfter(int index, T element){
    DLLNode<T> *newNode = new DLLNode<T>(element);
    if(isEmpty()){
        headNode->left = headNode->right = newNode;
        newNode->left = newNode->right = headNode;
    }
    // insertFront
    else if(index ==0 ){
        //先將newNode與 左右Node串上
        newNode->left = headNode;
        newNode->right = headNode->right;
        //再透過 左方Node 改 左右Node的L/R指向
        headNode->right->left = newNode;
        headNode->right = newNode;
    }
    // insertAfter Node i
    else{
        DLLNode<T> *current = getAddr(index);
        //先將newNode與 左右Node串上
        newNode->left = current;
        newNode->right = current->right;
        //再透過 左方Node 改 左右Node的L/R指向
        current->right->left = newNode;
        current->right = newNode;
    }
    size++;
}

template <class T>
void DLList<T>::deleteNode(int index){
    if(isEmpty()){cout << "Empty!!" << endl;}
    else{
        DLLNode<T> *current = getAddr(index);
        current->left->right = current->right;
        current->right->left = current->left;
        delete current;
    }
    size--;
}

template <class T>
ostream& operator<<(ostream& os,DLList<T>& dll){
    DLLNode<T> *current = dll.headNode->right;
    os << "[Head]<->";
    while(current->right!=dll.headNode){
        os << "[" << current->data << "]<->";
        current = current->right;
    }
    os << "[" << current->data << "]\n";
    return os;
}
#endif
