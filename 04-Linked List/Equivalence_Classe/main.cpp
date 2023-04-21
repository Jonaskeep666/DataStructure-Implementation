#include <iostream>
//#include "template_sll.hpp"
#include "stack.hpp"
using namespace std;

struct polyPair{
    int a;
    int b;
    void set(int a_,int b_){a=a_;b=b_;}
};

class Node{
    friend void equivalence(polyPair *polySet,int pairNums, int polyNums);
    friend void equivalenceRe(polyPair *polySet,int pairNums, int polyNums);
    friend void printSeqArray(Node **seq ,int polyNums);

    public:
        Node(){ next = 0;}
        Node(int term, Node* link=0){
            data = term;
            next = link;
        }
    protected:
        int data;
        Node* next;
};

enum Boolean {F,T};
typedef Node* NodePtr;

void printSeqArray(Node **seq ,int polyNums){
    for(int i=0;i<polyNums;++i){
        Node* current=seq[i];
        cout << i <<":\t";
        while(current){
            cout << current->data << ",";
            current = current->next;
        }
        cout << endl;
    }
}

// 找 等價類 的函數 (需要先在class Node中 friend起來)
void equivalence(polyPair *polySet,int pairNums, int polyNums){
    Node **seq = new Node*[polyNums];     //宣告一個 指向Node的指標陣列，需要用一個「雙重指標」接住
    Boolean *out = new Boolean[polyNums]; //宣告一個 enum陣列，每個元素只有(0,1)=(F,T)兩種可能
    for(int i=0;i<polyNums;++i){ seq[i]=0; out[i]=F; }
    for(int i=0;i<pairNums;++i){
        Node* x = new Node(polySet[i].a);
        Node* y = new Node(polySet[i].b);
        x->next = seq[polySet[i].b];
        seq[polySet[i].b] = x;
        y->next = seq[polySet[i].a];
        seq[polySet[i].a] = y;
    }
    printSeqArray(seq,polyNums);

    for(int i=0;i<polyNums;++i){
        if(out[i] == F){
            cout << endl;
            cout << "New class: "<< i << ",";
            out[i] = T;
        }
        Node* current=seq[i];
        Node* nextNode=0;
        Node* stackTop=0;
        while(1){
            while(current){
                if(out[current->data] == F){
                    out[current->data] = T;
                    cout << current->data <<",";

                    nextNode = current->next;
                    current->next = stackTop;   //Link stack (把還沒去的seq[i]串起來 成為 一個類stack)
                    stackTop = current;         //Push currentNode to the stack <- top (標示下次要去的seq[i])
                    current = nextNode;
                }
                else current = current->next;
            }
            //when current = null -> time to back! （直接回到 top指向Node[i]，並進入seq[i])
            if(!stackTop) break;
            else{
                current = seq[stackTop->data];  //進入 top指向Node[i]，並進入seq[i]
                //Pop top element (已經去過的seq[i]，下次不必再去，將Top更新成 上一個沒進去的seq[i])
                stackTop = stackTop->next;      
            }
        }   
    }
    cout << endl;
    // 再次印出 分類用的指標陣列seq[i] 
    // -> 會發現與原本的seq[i]不同，有節點沒有串在上面
    // -> 進而導致 未來根據seq[i] 釋放記憶體時，會產生「記憶體洩漏」
    printSeqArray(seq,polyNums);

    for(int i=0;i<polyNums;++i){
        while(seq[i]){
            Node* delNode = seq[i];
            seq[i] = delNode->next;
            delete delNode;
        }
        delete [] seq; delete [] out;
    }
}

// 找 等價類 的函數 (改良方法:用一個真的Stack去存)
void equivalenceRe(polyPair *polySet,int pairNums, int polyNums){
    Node **seq = new Node*[polyNums];     //宣告一個 指向Node的指標陣列，需要用一個「雙重指標」接住
    Boolean *out = new Boolean[polyNums]; //宣告一個 enum陣列，每個元素只有(0,1)=(F,T)兩種可能
    for(int i=0;i<polyNums;++i){    
        seq[i]=0;   //每個指標元素 都指向Null
        out[i]=F;  
    }
    // 第一階段：將等價對(pairs) 塞進 分類用的指標陣列
    for(int i=0;i<pairNums;++i){
        Node* x = new Node(polySet[i].a);
        Node* y = new Node(polySet[i].b);

        x->next = seq[polySet[i].b];
        seq[polySet[i].b] = x;
        y->next = seq[polySet[i].a];
        seq[polySet[i].a] = y;
    }
    printSeqArray(seq,polyNums); // 印出 分類指標陣列seq[i] 看看
    // 第二階段：開始分類
    for(int i=0;i<polyNums;++i){
        if(out[i] == F){
            cout << endl;
            cout << "New class: "<< i << ",";
            out[i] = T;
        }
        Stack<Node*> stack(10);
        Node* current=seq[i];

        while(1){
            while(current){
                if(out[current->data] == F){
                    out[current->data] = T;
                    cout << current->data <<",";

                    stack.Push(current);
                    current = seq[current->data];
                }
                else current = current->next;
            }
            if(!stack.isEmpty()) stack.Pop(current);
            if(!current) break;
        }   
    }
    cout << endl;
    // 第三階段：將seq[i]中指向的Node都free/delete掉
    for(int i=0;i<polyNums;++i){
        while(seq[i]){
            Node* delNode = seq[i];
            seq[i] = delNode->next;
            delete delNode;
        }
        delete [] seq; delete [] out;
    }
}

int main(void){
    polyPair polySet[9]={{0,4},{3,1},{6,10},{8,9},{7,4},{6,8},{3,5},{2,11},{11,0}};
    equivalenceRe(polySet,sizeof(polySet)/sizeof(polyPair),12);
}
