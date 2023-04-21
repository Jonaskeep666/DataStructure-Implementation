#ifndef _REDBLACK_HPP_
#define _REDBLACK_HPP_

#include <iostream>
#include <iomanip>
#include "stack.hpp"
using namespace std;

enum Color{Red,Black};

ostream& operator<<(ostream& os, enum Color c){
    if(c == Red) os << "Red";
    else os << "Black";
    return os;
}

struct RBNode{
    int key;
    enum Color color;
    RBNode *LChild,*RChild,*Parent;
    void setNode(int k=0){
        key = k; color = Red;
        LChild = 0; RChild = 0; Parent = 0;
        }
};

ostream& operator<<(ostream& os, RBNode* node){
    if(node){
        os << "(" << setw(2) << node->key << ")[" 
        << setw(5) << node->color << "]";
    }
    else os << "NULL";

    return os;
}

class RBTree{
    public:
        RBTree(){root = 0;}
        bool isEmpty(){return root == 0;}

        // Access
        bool isBlack(RBNode* u);            // 判斷 Node 的 Color，用意：若 u不存在，顏色是「黑色」
        bool isRed(RBNode* u);
        RBNode* grantpa(RBNode* u);         // 回傳 Node u 的 grandparent Node
        RBNode* uncle(RBNode* u);           // 回傳 Node u 的 uncle Node
        RBNode* sibling(RBNode* u);         // 回傳 Node u 的 sibling Node
        
        void buildTree();

        // Rotation 
        RBNode* leftRotate(RBNode* a);      // 以 Node a 為支點，向左轉
        RBNode* rightRotate(RBNode* a);     // 以 Node a 為支點，向右轉

        // Insert
        RBNode* insertInBST(int newkey);    // Node with Parent 指標的 BST Insert函數
        void fixInsert(RBNode* u);          // 以 Node u 為起點「往上調整」成 紅黑樹
        void insertNode(int newkey);        // Red-Black Tree Insert 函數

        // Delete
        RBNode* searchInBST(int key);       // 尋找 刪除點的位置 並回傳
        void fixDelete(RBNode* u);          // 以 u = Black Leaf 有4種Case 要修正
        void deleteNode(int delkey);        // Red-Black Tree Delete 函數

        // Output
        void printRBTree(){ 
            if(isEmpty()){ cout << "Empty tree!" << endl; return; }
            else { 
                cout << setw(13) << "";
                cout << setw(12) << "LChild|";
                cout << setw(12) << "RChild|";
                cout << setw(12) << "Parent|" <<endl;
                cout << setfill('-') << setw(49) << "" << endl;
                cout << setfill(' ');
                printRBTree(root); 
            }
        }
        void printRBTree(RBNode* start);
        void inorder(){inorder(root);};
        void inorder(RBNode* c){
            if(c){
                inorder(c->LChild);
                cout << c <<endl;
                inorder(c->RChild);
            }
        }

        // Test
        int count(int c){
            if(c==1) return count(root,0);
            else return count(root);
        }

        int count(RBNode* node,int cnt){
            if(node){
                cnt++;
                cnt = count(node->LChild,cnt);
                cnt = count(node->RChild,cnt);
            }
            return cnt;
        }
        int count(RBNode* node){
            int cntL=0,cntR=0;
            if(node){
                cntL = count(node->LChild);
                cntR = count(node->RChild);
                return cntL+cntR+1;
            }
            else return cntL+cntR;
        }

    private:
        RBNode* root;
};

// Access
bool RBTree::isBlack(RBNode* u){
    if(u){
        if(u->color == Black) return true;
        else return false;
    }
    else return true;
}
bool RBTree::isRed(RBNode* u){
    if(!isBlack(u)) return true;
    return false;
}
RBNode* RBTree::grantpa(RBNode* u){
    if(u == root){
        cout << "Root doesn't have grandpa." <<endl;
        return 0;
    }
    else{
        if(u->Parent->Parent) return u->Parent->Parent;
        else {
            cout << "The node doesn't have grandpa." <<endl;
            return 0;
        }
    }
}
RBNode* RBTree::uncle(RBNode* u){
    if(grantpa(u) && grantpa(u)->RChild && grantpa(u)->LChild){
        // 若「父點 = 祖父左孩」且「右孩存在」-> uncle 是 祖父右孩 
        if(u->Parent == grantpa(u)->LChild)
            return grantpa(u)->RChild;
        else if(u->Parent == grantpa(u)->RChild)
            return grantpa(u)->LChild;
    }
    cout << "The node doesn't have uncle." <<endl;
    return 0;
}
RBNode* RBTree::sibling(RBNode* u){
    // 若「父點 & 其兩子」皆存在 -> 才可能有 Sibling
    if(u->Parent && u->Parent->RChild && u->Parent->LChild){
        if(u == u->Parent->LChild) return u->Parent->RChild;
        if(u == u->Parent->RChild) return u->Parent->LChild;
    }
    cout << "The node doesn't have sibling." <<endl;
    return 0;
}

// Rotation 
RBNode* RBTree::leftRotate(RBNode* a){
    RBNode* b = a->RChild;

    // 一次旋轉 有6個指標要改

    // (1) b的父指標 指向 a的父點
    b->Parent = a->Parent;
    // (2,3) a的右孩 指向 b的左孩；「若b左孩存在」則更新 b左孩 的 父指標 = a
    a->RChild = b->LChild;
    if(b->LChild) b->LChild->Parent = a;
    // (4,5) b的LChild指向a，並更新 a的父指標 = b
    b->LChild = a;
    a->Parent = b;

    // (6) 讓 b現在的父點 指向自己
    if(b->Parent){
        if(b->key > b->Parent->key) b->Parent->RChild = b;
        else b->Parent->LChild = b;
    }
    // 若 b的父點 = NULL，表示 b為root
    else root = b;
    
    return b;   
}
RBNode* RBTree::rightRotate(RBNode* a){
    RBNode* b = a->LChild;

    b->Parent = a->Parent;

    a->LChild = b->RChild;
    if(b->RChild) b->RChild->Parent = a;

    b->RChild = a;
    a->Parent = b;

    if(b->Parent){
        if(b->key > b->Parent->key) b->Parent->RChild = b;
        else b->Parent->LChild = b;
    }
    else root = b;

    return b;
}

// Insert
RBNode* RBTree::insertInBST(int newkey){
    RBNode* newNode = new RBNode;
    newNode->setNode(newkey);

    // Insert root
    if(isEmpty()){ root = newNode; return newNode; }

    RBNode* current = root;
    
    while(current){
        if(newkey == current->key){
            cout << "The node has already been in the tree.";
            return current;
        }
        else if(newkey > current->key){
            if(current->RChild) current = current->RChild;
            else{
                current->RChild = newNode;
                newNode->Parent = current;
                return newNode;
            }
        }
        else if(newkey < current->key){
            if(current->LChild) current = current->LChild;
            else{
                current->LChild = newNode;
                newNode->Parent = current;
                return newNode;
            } 
        }
    }
}
void RBTree::fixInsert(RBNode* u){
    while(u!=root){
        // 若發生 連續 2 Red -> 判斷違規 2大類，若沒事，則將 u 指向其父點
        if(u->color == Red && u->Parent->color == Red){
            // Special Case
            if(!grantpa(u)) u = u->Parent; //若 grandpa不存在，令 u = u->Parent = root
            
            // Case A：LLr、LRr、RRr、RLr
            if(uncle(u) != NULL && uncle(u)->color == Red){

                    // Color change
                    u->Parent->color = Black;
                    uncle(u)->color = Black;
                    grantpa(u)->color = Red;

                    u = grantpa(u); // 上升2層，將 u 指向 grandpa
            }

            // Case B：LLb、LRb、RRb、RLb
            else{
                // Rotation：判斷 LL,LR or RR,RL
                if(u->Parent == grantpa(u)->LChild){    
                    if(u == u->Parent->LChild){ // LLb
                        // 以grantpa(u)為「支點」向右轉，轉完以後 將u重新指向「新支點」
                        u = rightRotate(grantpa(u)); 
                    }
                    else{                       // LRb
                        RBNode* subroot = grantpa(u);
                        subroot->LChild = leftRotate(u->Parent); // 以 u的父點為「支點」向左轉
                        u = rightRotate(subroot); // 以subroot為「支點」向右轉，轉完 將u指向「新支點」
                    }
                }
                else{
                    if(u == u->Parent->RChild){ // RRb
                        // 以grantpa(u)為「支點」向左轉，轉完以後 將u重新指向「新支點」
                        u = leftRotate(grantpa(u)); 
                    }
                    else{                       // RLb
                        RBNode* subroot = grantpa(u);
                        subroot->RChild = rightRotate(u->Parent); // 以 u的父點為「支點」向右轉
                        u = leftRotate(subroot); // 以subroot為「支點」向左轉，轉完 將u指向「新支點」
                    }
                }
                // Color change
                u->color = Black;
                if(u->LChild) u->LChild->color = Red;
                if(u->RChild) u->RChild->color = Red;
            }
        }
        else u = u->Parent;
    }
    root->color = Black;
}

void RBTree::insertNode(int newkey){
    RBNode* newNode = insertInBST(newkey);
    fixInsert(newNode);
}

// Delete

RBNode* RBTree::searchInBST(int key){
    RBNode* current = root;

    if(isEmpty()) return 0;
    while(current){
        if(key == current->key) return current;
        else if(key > current->key) current = current->RChild;
        else if(key < current->key) current = current->LChild;     
    }
    return 0;
}

void RBTree::fixDelete(RBNode* u){
    RBNode* current = u;

    while (current != root && current->color == Black) {
        // current 是 LChild
        if(current == current->Parent->LChild){
            // Sibling = Black
            if(sibling(current)->color == Black){
                // Case 1：Sibling = Black、Nephews = Black
                if(isBlack(sibling(current)->LChild) && isBlack(sibling(current)->RChild)){
                    sibling(current)->color = Red;  // S->red
                    current = current->Parent;      // u = p+Black
                    if(current->color == Red){
                        current->color = Black;
                        return;
                    }
                }
                else{
                    // Case 3：Sibling = Black、Near Nephew = Red、Far Nephew = Black
                    if(isRed(sibling(current)->LChild) && isBlack(sibling(current)->RChild)){
                        sibling(current)->color = Red;
                        sibling(current)->LChild->color = Black;
                        rightRotate(sibling(current));
                    }
                    // Case 4：Sibling = Black、Far Nephew = Red
                    else if(isRed(sibling(current)->RChild)){
                        sibling(current)->color = current->Parent->color;
                        current->Parent->color = Black;
                        sibling(current)->RChild->color = Black;
                        leftRotate(current->Parent);
                        return;
                    }
                }
            }
            // Sibling = Red
            else{
                // Case 2：Sibling = Red
                current->Parent->color = Red;
                sibling(current)->color = Black;
                leftRotate(current->Parent);
            }
        }
        // current 是 RChild
        else{
            // Sibling = Black
            if(sibling(current)->color == Black){
                // Case 1：Sibling = Black、Nephews = Black
                if(isBlack(sibling(current)->LChild) && isBlack(sibling(current)->RChild)){
                    sibling(current)->color = Red;  // S->red
                    current = current->Parent;      // u = p+Black
                    if(current->color == Red){
                        current->color = Black;
                        return;
                    }
                }
                else{
                    // Case 3：Sibling = Black、Near Nephew = Red、Far Nephew = Black
                    if(isRed(sibling(current)->RChild) && isBlack(sibling(current)->LChild)){
                        sibling(current)->color = Red;
                        sibling(current)->RChild->color = Black;
                        leftRotate(sibling(current));
                    }
                    // Case 4：Sibling = Black、Far Nephew = Red
                    else if(isRed(sibling(current)->LChild)){
                        sibling(current)->color = current->Parent->color;
                        current->Parent->color = Black;
                        sibling(current)->LChild->color = Black;
                        rightRotate(current->Parent);
                        return;
                    }
                }
            }
            // Sibling = Red
            else{
                // Case 2：Sibling = Red
                current->Parent->color = Red;
                sibling(current)->color = Black;
                rightRotate(current->Parent);
            }
        }
    }
    current->color = Black; //抵達root，將其色改為Black
}

void RBTree::deleteNode(int delkey){
    RBNode* delNote = searchInBST(delkey);

    if(!delNote){ cout << "The key doesn't exist."; return; }
    else{
        // 2 Child：找繼任者，並轉換成 Leaf 或 1 Child 的情形
        if(delNote->LChild  && delNote->RChild){
            RBNode* succNode = delNote->RChild;
            while(succNode->LChild)
                succNode = succNode->LChild;

            delNote->key = succNode->key; //將繼任者的「資料」 存入 current，但「不包含顏色」
            delNote = succNode;     // 將delNote指向「繼任者」
        }

        RBNode* Child = (delNote->LChild ? delNote->LChild:delNote->RChild);
        // Leaf 
        if(!Child){
            Child = delNote;        // 借用Child 指向 要刪去的點

            // 若 delNote = Red or root：直接刪除
            // 若 delNote = Black：4種 Case
            if(delNote->color == Black && delNote != root)
                fixDelete(delNote);

            // 刪除點的Parent->Child 指向 NULL
            if(delNote!=root){
                if(delNote == delNote->Parent->LChild) delNote->Parent->LChild = 0;
                else delNote->Parent->RChild = 0;   
            }
            else root = 0;

        }
        // 1 Child：將 Child的key 存入 delNote，刪掉 Child
        else delNote->key = Child->key;

        delete Child;
    }
}

// Output
void RBTree::printRBTree(RBNode* start){
    if(start){
        cout << start << ": ";

        if(start->LChild) cout << start->LChild << "|";
        else cout << setw(12) << " ---|";

        if(start->RChild) cout << start->RChild << "|";
        else cout << setw(12) <<" ---|";

        if(start->Parent) cout << start->Parent << "|" << endl;
        else cout << setw(13) <<" ---|\n";

        printRBTree(start->LChild);
        printRBTree(start->RChild);
    }
}

void aSetNode(RBNode** node,Color c,int j,int l=-1,int r=-1){

    node[j]->color = c;
    if(l>=0){
        node[j]->LChild = node[l]; node[l]->Parent = node[j];
    }
    if(r>=0){
        node[j]->RChild = node[r]; node[r]->Parent = node[j];
    }
}

void RBTree::buildTree(){
    int num[] = {36,16,52,4,24,41,55,3,9,22,27,48,1,7,10};
    int size = (int)sizeof(num)/sizeof(int);

    RBNode** node = new RBNode*[size];
    for(int i=0;i<size;++i){
        node[i] = new RBNode;
        node[i]->setNode(num[i]);
    }
    
    root = node[0];
    aSetNode(node,Black,0,1,2);
    aSetNode(node,Red,1,3,4);
    aSetNode(node,Black,2,5,6);
    aSetNode(node,Black,3,7,8);
    aSetNode(node,Black,4,9,10);
    aSetNode(node,Black,5,-1,11);
    aSetNode(node,Black,6);
    aSetNode(node,Black,7,12);
    aSetNode(node,Red,8,13,14);
    aSetNode(node,Black,9);
    aSetNode(node,Black,10);
    aSetNode(node,Red,11);
    aSetNode(node,Red,12);
    aSetNode(node,Black,13);
    aSetNode(node,Black,14);

}

#endif
