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
        TreeNode(){leftChild = rightChild = 0;res = false;}
        TreeNode(T d){
            data = d; res = false;
            leftChild = rightChild = 0;
        }
    private:
        T data;
        // For SAT problem
        bool res;
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

        void inorderStack(){inorderStack(root);}
        void inorderStack(TreeNode<T> *current);
        void preorderStack(){preorderStack(root);}
        void preorderStack(TreeNode<T> *current);
        void postorderStack(){postorderStack(root);}
        void postorderStack(TreeNode<T> *current);

        //Access
        TreeNode<T>* getAddr(int index);
        T getData(int index);
        void insert(int index,char dir,T d);

        //operate
        void copyTree(Tree& orig){ root = copyTree(orig.root); }
        TreeNode<T>* copyTree(TreeNode<T>* origNode);
        bool equalTree(Tree& t1,Tree& t2){ return equalTree(t1.root,t2.root);}
        bool equalTree(TreeNode<T>* r1,TreeNode<T>* r2);

        int PostOrderEval(){return PostOrderEval(root);}
        int PostOrderEval(TreeNode<T>* r);

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
            // cout<<"D("<<delNode->data<<"),"<<"["<< current->data <<"]"<<endl;
            delete delNode;
        }
        else{
            current = current->rightChild;
            // cout<<"R("<<current<<"),"<<endl;
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
        inorder(current->leftChild);
        visit(current);
        inorder(current->rightChild);
    }
}
template <class T>
void Tree<T>::preorder(TreeNode<T> *current){
    if(current){
        visit(current);
        preorder(current->leftChild);
        preorder(current->rightChild);
    }
}
template <class T>
void Tree<T>::postorder(TreeNode<T> *current){
    if(current){
        postorder(current->leftChild);
        postorder(current->rightChild);
        visit(current);
    }
}
template <class T>
void Tree<T>::levelorder(TreeNode<T> *current){
    if(current){
        Queue< TreeNode<T>* > q(10);
        while(current){
            visit(current);
            if(current->leftChild) q.Push(current->leftChild);
            if(current->rightChild) q.Push(current->rightChild);
            if(q.isEmpty()) return;
            q.Pop(current);
        } 
    }
}

//******* orderStack *******

// 左邊 -> 中間 -> 右邊
template <class T>
void Tree<T>::inorderStack(TreeNode<T> *current){
    Stack< TreeNode<T>* > stack(10);
    while(1){
        //Phase 1: 衝到最左邊
        while(current){
            stack.Push(current);
            current = current->leftChild;
        }
        //Phase 2: 印出 往右走
        if(!stack.isEmpty()){
            stack.Pop(current);     
            visit(current);
            current = current->rightChild;
        }
        else return;
    }
}

// 中間 -> 左邊 -> 右邊
template <class T>
void Tree<T>::preorderStack(TreeNode<T> *current){
    Stack< TreeNode<T>* > stack(10);
    while(1){
        //Phase 1: 往左邊衝，邊衝邊印，直到最左邊
        while(current){
            visit(current);
            stack.Push(current);
            current = current->leftChild;
        }
        //Phase 2: Pop 往右走
        if(!stack.isEmpty()){
            stack.Pop(current);
            current = current->rightChild;
        }
        else return;
    }
}

// 左邊 -> 右邊 -> 中間
template <class T>
void Tree<T>::postorderStack(TreeNode<T> *current){
    Stack< TreeNode<T>* > stack(10);
    TreeNode<T> *lastpop = current;

    while(1){
        //Phase 1: 衝到最左邊
        while(current && current->leftChild != lastpop && current->rightChild != lastpop){
            stack.Push(current);
            current = current->leftChild;
        }

        //Phase 2: 往右走 or 印出
        current = stack.Top();  

        //[Case 1] currentNode 左右無子 -> Pop 並 印出 -> 令current = stack.Top()
        if(!current->leftChild && !current->rightChild){
            stack.Pop(lastpop);
            visit(current);
            if(!stack.isEmpty()) current = stack.Top();
        }
        //[Case 2] currentNode 無右子 且 左邊已經走過 -> Pop 並 印出 -> 令current = stack.Top()
        else if(!current->rightChild && current->leftChild == lastpop){
            stack.Pop(lastpop);
            visit(current);
            if(!stack.isEmpty()) current = stack.Top();
        }
        //[Case 3] currentNode 右邊已經走過 -> Pop 並 印出 -> 令current = stack.Top()
        else if(current->rightChild == lastpop){
            stack.Pop(lastpop);
            visit(current);
            if(!stack.isEmpty()) current = stack.Top();
        }
        //只要有右邊沒走過，往右走
        else if(current->rightChild != lastpop){
            current = current->rightChild;
        }
        if(stack.isEmpty()) return;  
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
            if(current->leftChild) q.Push(current->leftChild);
            if(current->rightChild) q.Push(current->rightChild);
            if(q.isEmpty()) break;
            q.Pop(current);
            count++;
        } 
        return current;
    }
    else{
        //cout << "Tree is Empty!" << endl;
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
    }
    else cout << "The node isn't exist.";
}

//******* Operate *******

template <class T>
TreeNode<T>* Tree<T>::copyTree(TreeNode<T>* origNode){
    if(origNode){
        TreeNode<T>* newNode = new TreeNode<T>;
        newNode->data = origNode->data;
        newNode->leftChild = copyTree(origNode->leftChild);
        newNode->rightChild = copyTree(origNode->leftChild);
        return newNode;
    }
    else return 0;
}

template <class T>
bool Tree<T>::equalTree(TreeNode<T>* r1,TreeNode<T>* r2){
    if(!r1 && !r2) return true;
    if((r1 && r2) && (r1->data == r2->data) 
        && equalTree(r1->leftChild,r2->leftChild) 
        && equalTree(r1->rightChild,r2->rightChild) )
        return true;
    else return false;
}

template <class T>
int Tree<T>::PostOrderEval(TreeNode<T>* r){
    int op1,op2;
    if(r){
        PostOrderEval(r->leftChild);
        PostOrderEval(r->rightChild);
        switch (r->data){
            case '~':
                op1 = r->rightChild->res;
                r->res = !op1;
                break;
            case '*':
                op1 = r->rightChild->res;
                op2 = r->leftChild->res;
                r->res = op1 && op2;
                break;
            case '+':
                op1 = r->rightChild->res;
                op2 = r->leftChild->res;
                r->res = op1 || op2;
                break;
            case '1':
                r->res = r->data - 48;
                break;
            case '0':
                r->res = r->data - 48;
                break;
        }
        return r->res;
    }
    return -1;
}

#endif
