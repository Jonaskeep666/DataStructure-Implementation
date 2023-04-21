#ifndef _AVL_HPP_
#define _AVL_HPP_

#include <iostream>
#include "stack.hpp"
using namespace std;

int maxValue(int a, int b){
    return a>b?a:b;
}

struct AVLnode{
    int key;
    int height;
    AVLnode *LChild,*RChild;
    void setNode(int k=0,int h=0){
        key = k; height=h;
        LChild = 0;
        RChild = 0;
        }
};

ostream& operator<<(ostream& os, AVLnode* node){
    os << "(" << node->key << ")[" << node->height << "]";
    return os;
}

class AVLtree{
    public:
        AVLtree(){root = 0;}
        bool isEmpty(){return root == 0;}

        // Height & Balance Factor
        int getBF(AVLnode* node);       // 計算 node 的 Balance Factor
        int getHeight(AVLnode* node);   // 計算 node 的 高度(1 + maxChild的高度)
        void updataHeight(AVLnode* node);

        // Rotation & Rebalance
        AVLnode* leftRotate(AVLnode* a);    // 以 Node a 為支點，向左轉
        AVLnode* rightRotate(AVLnode* a);   // 以 Node a 為支點，向右轉
        void rebalance(AVLnode* parent, AVLnode* current);  // 適用 迭代法 的 再平衡

        // Maintenance (Iteration)
        void insertNode(int newkey);
        void deleteNode(int delkey);

        // Maintenance (Recursion)
        void insertR(int newkey){ root = insertRecur(newkey,root);}
        AVLnode* insertRecur(int newkey,AVLnode* current);
        void deleteR(int delkey){ root = deleteRecur(delkey,root);}
        AVLnode* deleteRecur(int delkey,AVLnode* current);

        // Output
        void printAVLtree(){ 
            if(isEmpty()){ cout << "Empty tree!" << endl; return; }
            else { cout << "\t LChild\t RChild" <<endl; printAVLtree(root); }
        }
        void printAVLtree(AVLnode* start);

    private:
        AVLnode* root;
};

// Height & Balance Factor

int AVLtree::getBF(AVLnode* node){
    int hL = getHeight(node->LChild);
    int hR = getHeight(node->RChild);
    return (hL-hR);
}

int AVLtree::getHeight(AVLnode* node){
    if(node) return node->height;
    else return 0;
}

void AVLtree::updataHeight(AVLnode* node){
    // 若無子 current高度 = 1，若有任一子 高度為h -> current高度 = 1+h
    node->height = 1 + maxValue(getHeight(node->LChild),getHeight(node->RChild));
}

// Rotation & Rebalance

AVLnode* AVLtree::leftRotate(AVLnode* a){   //向左轉(表示右邊比較長)
    AVLnode* b = a->RChild;
    a->RChild = b->LChild;
    b->LChild = a;
    // update height：a,b 兩個 Node的高度會改變
    updataHeight(a);
    updataHeight(b);
    return b;
}
AVLnode* AVLtree::rightRotate(AVLnode* a){  //向右轉(表示左邊比較長)
    AVLnode* b = a->LChild;
    a->LChild = b->RChild;
    b->RChild = a;
    // update height：a,b 兩個 Node的高度會改變
    updataHeight(a);
    updataHeight(b);
    return b;
}
void AVLtree::rebalance(AVLnode* parent, AVLnode* current){

    // 將parentChild 指向 parent 的 LChild指標 或 RChild指標
    // 使 *parentChild 可修改 parent->LChild 的指向
    AVLnode** parentChild = 0;  

    // 若 current ≠ root，將 parentChild 指向 parent 的 LChild指標 或 RChild指標
    // 若 current = root，將 parentChild 指向 root指標，使 *parentChild 可修改 root的指向
    if(current!=root){          
        if(current->key > parent->key) parentChild = &parent->RChild;
        else parentChild = &parent->LChild;
    }
    else parentChild = &root;

    if(getBF(current) >= 2){  // BF(c)=2 表示「左子樹」較高 -> 刪去點在右子樹中 -> LL or LR
        if(getBF(current->LChild) >= 0){    // 左子樹的左邊比較長 -> LL
            *parentChild = rightRotate(current);
        }
        else {  // 左子樹的右邊比較長 -> LR
            current->LChild = leftRotate(current->LChild); //先向左轉
            *parentChild = rightRotate(current);
        }
    }
    else if(getBF(current) <= -2){ // BF(c)=-2 表示「右子樹」較高 -> 刪去點在左子樹中 -> RR or RL
        if(getBF(current->RChild) >= 0){    // 右子樹的左邊比較長 -> RL
            current->RChild = rightRotate(current->RChild); //先向右轉
            *parentChild = leftRotate(current);
        }
        else {  // 右子樹的右邊比較長 -> RR
            *parentChild = leftRotate(current);
        }
    }
}


// Maintenance(Iteration)

// Insert 方法1：遞迴法(最快)，因為 計算高度 需要從底往回算
// Insert 方法2：迭代法，用 stack 儲存路徑 取代遞迴

void AVLtree::insertNode(int newkey){
    AVLnode* newNode = new AVLnode;
    newNode->setNode(newkey,1);

    Stack<AVLnode*> s(20); // 用 Stack 來存放 搜尋路徑

    if(isEmpty()){
        root = newNode;
        return;
    }
    // Phase 1：Search 插入位置，並插入newNode
    AVLnode* current = root;

    while(current){
        s.Push(current);
        if(newkey == current->key){
            cout << "Node exist."; return;
        }
        else if(newkey > current->key) current=current->RChild;
        else if(newkey < current->key) current=current->LChild;
    }

    current = s.Top();
    if(newkey > current->key) current->RChild = newNode;
    else current->LChild = newNode;

    // Phase 2：在路徑 root -> newNode 之間，updateHeight & rebalance
    // 作法：新增newNode之後，往回走，計算路徑中 每個Node的「最大高度」並根據「BF」調整平衡樹

    while(!s.isEmpty()){
        AVLnode* parent = root; //宣告 current 的 parent = parent
        s.Pop(current);
        if(current!=root) parent = s.Top();

        updataHeight(current);      // UpdateHeight
        rebalance(parent,current);  // Check Balance Factor & Rebalance
    }
}

void AVLtree::deleteNode(int delkey){
    // Phase 1：Search 要刪除的節點位置，並找「Inorder 繼任者/前任者」放該位置
    AVLnode* current = root;
    Stack<AVLnode*> s(20); // 用 Stack 來存放 搜尋路徑

    while(current){
        s.Push(current);
        if(delkey == current->key) break;
        else if(delkey > current->key) current=current->RChild;
        else if(delkey < current->key) current=current->LChild;
    }

    if(!current){
        cout << "The key isn't exist.";
        return;
    }

    s.Pop(current);                     //取出 刪除點
    AVLnode* parent = root;             //宣告 current 的 parent = parent
    if(current!=root) parent = s.Top(); // 取出 刪除點的Parent

    // Case 1 & 2：current 無子 or 有一子
    if(!current->LChild || !current->RChild){
        AVLnode* Child = current->LChild ? current->LChild:current->RChild;
        if(!Child){ // Case 1：current 無子 -> 直接將 current 刪掉 -> 並讓其Parent 指向 NULL
            Child = current;        // 借用Child 指向 要刪去的點

            if(current!=root){
                // 刪除點的Parent->Child 指向 NULL
                if(current == parent->LChild) parent->LChild = 0;
                else parent->RChild = 0;       
                current = parent;   // 將 current 指向 刪除點的Parent
            }
            else root = 0;
        }           // Case 2：current 有一子 -> 將 Child 存入 current，刪掉 Child -> 並讓其Parent 指向 current  
        else *current = *Child;

        delete Child;
    }
    // Case 3：current 有兩子 -> 找繼任者（右樹 最左者(最小值)) 與其交換
    else{ 
        s.Push(current);
        AVLnode* succNode = current->RChild;
        while(succNode->LChild){
            s.Push(succNode);
            succNode = succNode->LChild;
        }
        current->key = succNode->key; //將繼任者的「資料」 存入 current，但「不包含高度」

        // 刪去 succNode
        parent = s.Top();   //找出 succNode 的 Parent，將 parent->LChild = NULL
        parent->LChild = 0;
        delete succNode;
        s.Pop(current);     //將 Leaf = succNode 的 Parent Pop出，存入 current
    }

    // 以上將 current 指向 回朔點，並將其統一放回Stack頂端
    s.Push(current);

    // Phase 2：在路徑 root -> 回朔點(delNode or Leaf) 之間，updateHeight & rebalance
    // 作法：往回走，計算路徑中 每個Node的「最大高度」並根據「BF」調整平衡樹
    while(!s.isEmpty()){
        s.Pop(current);
        if(current!=root) parent = s.Top(); //取出 current 的 parent

        updataHeight(current);      // UpdateHeight
        rebalance(parent,current);  // Check Balance Factor & Rebalance
    }
}

// Maintenance(Recursion)

AVLnode* AVLtree::insertRecur(int newkey,AVLnode* current){
    // Phase 1：Search 插入位置，並插入newNode
    if(!current){
        current = new AVLnode;
        current->setNode(newkey);
    }
    else{
        if(newkey > current->key) 
            current->RChild = insertRecur(newkey,current->RChild);
        else if(newkey < current->key) 
            current->LChild = insertRecur(newkey,current->LChild);
        else return current;    
    }

    // Phase 2：在路徑 root -> newNode 之間，updateHeight & rebalance
    // 作法：遞迴到Leaf，新增newNode之後，往回走，計算路徑中 每個Node的「最大高度」並根據「BF」調整平衡樹

    updataHeight(current);  // UpdateHeight

    // Check Balance Factor & Rebalance
    if(getBF(current) >= 2){  // BF(c)=2 表示「左子樹」較高 -> 刪去點在右子樹中 -> LL or LR
        if(getBF(current->LChild) >= 0){    // 左子樹的左邊比較長 -> LL
            return rightRotate(current);
        }
        else {  // 左子樹的右邊比較長 -> LR
            current->LChild = leftRotate(current->LChild); //先向左轉
            return rightRotate(current);
        }
    }
    else if(getBF(current) <= -2){ // BF(c)=-2 表示「右子樹」較高 -> 刪去點在左子樹中 -> RR or RL
        if(getBF(current->RChild) >= 0){    // 右子樹的左邊比較長 -> RL
            current->RChild = rightRotate(current->RChild); //先向右轉
            return leftRotate(current);
        }
        else {  // 右子樹的右邊比較長 -> RR
            return leftRotate(current);
        }
    }
    return current;
}

AVLnode* AVLtree::deleteRecur(int delkey,AVLnode* current){
    // Phase 1：Search 要刪除的節點位置，並找「Inorder 繼任者/前任者」放該位置
    if(delkey > current->key) 
        current->RChild = deleteRecur(delkey,current->RChild);
    else if(delkey < current->key) 
        current->LChild = deleteRecur(delkey,current->LChild);
    else{
        // Case 1 & 2：current 無子 or 有一子
        if(!current->LChild || !current->RChild){
            AVLnode* Child = current->LChild ? current->LChild:current->RChild;
            if(!Child){ // Case 1：current 無子 -> 直接將 current 刪掉 -> 並讓其Parent 指向 NULL
                Child = current;
                current = 0;
            }           // Case 2：current 有一子 -> 將 Child 存入 current，刪掉 Child -> 並讓其Parent 指向 current
            else *current = *Child;

            delete Child;
        }
        // Case 3：current 有兩子 -> 找繼任者（右樹 最左者(最小值)) 與其交換
        else{ 
            AVLnode* succNode = current->RChild;
            while(succNode->LChild)
                succNode = succNode->LChild;
            current->key = succNode->key; //將繼任者的「資料」 存入 current，但「不包含高度」

            // 以current->RChild為起點，尋找並刪除 繼任者Node
            current->RChild = deleteRecur(succNode->key,current->RChild); 
        }
    }
    if(!current) return current;  //若current = 0，表示達到 Leaf，可以往回走  

    // Phase 2：在路徑 root -> 回朔點(delNode or Leaf) 之間，updateHeight & rebalance
    // 作法：遞迴到Leaf，往回走，計算路徑中 每個Node的「最大高度」並根據「BF」調整平衡樹

    updataHeight(current);      // UpdateHeight
    
    // Check Balance Factor & Rebalance
    if(getBF(current) >= 2){  // BF(c)=2 表示「左子樹」較高 -> 刪去點在右子樹中 -> LL or LR
        if(getBF(current->LChild) >= 0){    // 左子樹的左邊比較長 -> LL
            return rightRotate(current);
        }
        else {  // 左子樹的右邊比較長 -> LR
            current->LChild = leftRotate(current->LChild); //先向左轉
            return rightRotate(current);
        }
    }
    else if(getBF(current) <= -2){ // BF(c)=-2 表示「右子樹」較高 -> 刪去點在左子樹中 -> RR or RL
        if(getBF(current->RChild) >= 0){    // 右子樹的左邊比較長 -> RL
            current->RChild = rightRotate(current->RChild); //先向右轉
            return leftRotate(current);
        }
        else {  // 右子樹的右邊比較長 -> RR
            return leftRotate(current);
        }
    }
    return current;
}

// Output
void AVLtree::printAVLtree(AVLnode* start){
    if(start){
        if(start->key<10) cout << start <<":\t";
        else cout << start <<":";

        if(start->LChild) cout << start->LChild <<",\t";
        else cout <<" ---,\t";
        if(start->RChild)cout << start->RChild << endl;
        else cout <<" ---\n";

        printAVLtree(start->LChild);
        printAVLtree(start->RChild);
    }
    else return;
}

#endif
