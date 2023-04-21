#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <iomanip>
#include "stack.hpp"
#include "queue.hpp"
using namespace std;

// 本程式 不採用 Index=0 的元素 A[0]，從 Index=1 開始（除了 MST Set)

#define ABS(X) (X)>=0?(X):((-1)*(X))


class ALGraph;
struct Vertex{
    void setVtx(int no_, int w){
        no = no_; next = 0;
        weight = w;
    }
    int no;
    int weight;
    Vertex* next;
};
class List{
    friend class ALGraph;

    public:
        List(){first=rear=0; size=0;}
        // Access
        Vertex* searchNode(int x);

        // Maintain

        // 插入 Node(x) & Edge(i,x)的權值w & 註記是否是無向圖的重複邊
        Vertex* insertBack(int x, int w);   
        void deleteNode(int x);             // 刪除 Node(x)
        void deleteList();                  // 刪除 整個List

        // Output
        void printList();

    private:
        Vertex* first; 
        Vertex* rear;
        int size;       // List 的大小
}; 

struct EdgeNode{
    void set(int s, int e, int w){
        weight = w; start = s; end = e;
    }
    int weight;
    int start;
    int end;
};

struct VHeapNode{
    void set(int no_,int cst){
        no = no_;
        cost = cst;
    }
    int no;
    int cost;
};

class VertexHeap{
    friend class ALGraph;

    public:
        VertexHeap(int n){
            capacity = n+1;
            heap = new VHeapNode[capacity];
            for(int i=0;i<capacity;++i)
                heap[i].set(0,0);
            size = 0;
        }
        bool isEmpty(){return size==0;}

        //access
        VHeapNode Top(){return heap[1];}
        int findPos(int no);

        //maintainance
        void Push(VHeapNode newNode);
        void Pop(VHeapNode& max);

        //operation
        void adjust(int rootIdx);   // 將 rootIdx 往下沉調整
        void adjustUp(int Idx);     // 將 Idx 往上浮調整
        void buildHeap();

    private:
        VHeapNode *heap;
        int size;
        int capacity;
};

class ALGraph{
    friend class List;
    friend class Set;
    friend class EdgeHeap;

    public:
        ALGraph(int c, bool direction){
            vtxList = new List[c];
            for(int i=0;i<c;++i){
                vtxList[i].first = vtxList[i].rear = 0;
                vtxList[i].size = 0;
            }
            capacity = c;
            n=0; e=0;
            dir = direction;
        }
        bool IsEmpty(){ return n==0;}

        // Maintain
        int vtxDegree(int x);      // 計算 點c 的Degree

        void InsertVertex(int v);           // insert 點v
        void InsertEdge(int u, int v, int w);      // insert Edge(u,v) + weight
        void DeleteVertex(int v);           // Delete 點v & 相關的Edge
        void DeleteEdge(int u, int v);      // Delete Edge(u,v)

        // Output
        void printList();

        // MST
        void printMST(int *parent,int *minCost, int mstIdx, int mstSum);
        int MST_Prim(int s);   // 以 起點s 開始，利用 Prim's Algo 產生「最小生成樹」

    private:
        List* vtxList;  // 相鄰串列
        int capacity;   // 相鄰串列 的「最大」大小(最多可容納頂點數)
        int n;          // Vertex 總數
        int e;          // Edge 總數
        int dir;        // T:有向圖 F:無向圖
};

// ---------------------------------------------------------------------------------------
// List

// Access
Vertex* List::searchNode(int x){
    Vertex* current = first;
    if(first == 0) return 0;
    while(current){
        if(current->no == x) return current;
        current = current->next;
    }
    return 0;
}
// Maintain
Vertex* List::insertBack(int x, int w){

    // 若 Vertex(x) 已存在，則退出
    if(searchNode(x)) return 0;

    Vertex* newNode = new Vertex;
    newNode->setVtx(x,w);

    size++;
    // newNode = 首元素
    if(first == 0){
        first = newNode; 
        rear = first;
        return newNode;
    } 
    // newNode ≠ 首元素
    else{
        rear->next = newNode;
        rear = newNode;
        return newNode;
    }
}
void List::deleteNode(int x){
    Vertex* delNode = searchNode(x);
    
    // 若 Vertex(c) 不存在，則退出
    if(delNode == 0){
        cout << "Vertex "<< x << " doexn't exist." <<endl;
        return;
    }
    else{
        size--;

        // delNode = 首元素
        if(first == delNode){
            first = delNode->next;
            // delNode = 尾元素
            if(rear == delNode) rear = 0;
        }
        // delNode ≠ 首元素
        else{
            Vertex* prev = first;
            while(!(prev->next == delNode)){
                prev = prev->next;
            }
            prev->next = delNode->next;
            // delNode = 尾元素
            if(delNode == rear) rear = prev;
        }
        delete delNode;
    }
}
void List::deleteList(){

    if(first == 0) return;  // List 為空
    else{
        Vertex* prev = first;
        Vertex* delNode = first->next;
        
        // 若只有一個 Node，直接刪除
        if(first == rear){
            delete first; 
            first = rear = 0;
            return;
        }

        // 若有≥2個Node，先把中間的元素 刪除，在刪除首尾兩端
        while(first->next != rear){
            prev->next = delNode->next;
            delete delNode;
            delNode = prev->next;
        }
        delete rear; delete first;
        first = rear = 0;
    }

}
// Output
void List::printList(){
    Vertex* current = first;
    if(first == 0){
        cout << "List is empty!" <<endl; return;
    }
    while(current){
        cout << current->no << "[" << current->weight << "]"<< ",\t";
        current = current->next;
    }
    cout << endl;
}

// ---------------------------------------------------------------------------------------
// EdgeHeap

//Access
int VertexHeap::findPos(int no){
    for(int i=1;i<=size;++i)
        if(heap[i].no == no) return i;
    return 0;
}

//maintainance
void VertexHeap::Push(VHeapNode newNode){
    if(size == capacity){
        cout<<"Heap is full."<<endl;
        return;
    }

    size++;
    int newIndex = size;
    while(!(newIndex == 1) && (newNode.cost < heap[(newIndex)/2].cost)){
        heap[newIndex] = heap[(newIndex)/2]; //將Parent往下移動
        newIndex = newIndex/2;
    }
    heap[newIndex] = newNode; 
    
}
void VertexHeap::Pop(VHeapNode& min){
    if(isEmpty()){ cout<<"Empty!"<<endl; return;}
    
    min = heap[1];
    heap[1] = heap[size];
    size--;
    adjust(1);
}

//operation
void VertexHeap::adjust(int rootIdx){
    VHeapNode subroot = heap[rootIdx]; //暫存heap[rootIdx]
    int current = rootIdx;    //root = lastNode
    int minChild = current*2; //指向最小的孩子

    //當指向的孩子 沒有超出 heap的大小時，代表「還有子樹」
    while(minChild <= size){
        //比較 current 的兩個孩子 誰比較大，minChild指向小的孩子
        if(heap[minChild].cost > heap[minChild+1].cost && minChild < size){
            minChild++;
        }
        //若current已經 比 最小的孩子還小，則調整結束
        if(subroot.cost <= heap[minChild].cost) break; 

        heap[current] = heap[minChild]; //將小的孩子上浮
        current = minChild;             //將current下沉到「小的孩子」所在位置
        minChild = current*2;           //將minChild指向新的孩子的位置
    }
    heap[current] = subroot;
}
void VertexHeap::adjustUp(int Idx){
    VHeapNode tempNode = heap[Idx]; //暫存heap[rootIdx]
    int current = Idx;  
    int parent = Idx/2; //指向 Idx 的 parent

    // current 往上挑戰，直到 抵達 root
    while(current > 1){
        if(heap[parent].cost > tempNode.cost){  // 注意：不能用 heap[current].cost
            heap[current]=heap[parent]; // parent 下沈
            current /= 2;               // current 上浮
            parent = current/2;
        }
        else break;
    }
    heap[current] = tempNode;
}
void VertexHeap::buildHeap(){
    for(int i=(size/2);i>=1;--i) 
        adjust(i);
}


// ---------------------------------------------------------------------------------------
// ALGraph

// Maintain
int ALGraph::vtxDegree(int x){
    int idx = x;
    int cnt = 0;
    if(idx <= 0) return -1;

    // 無向圖：求 點c 的 Degree = vtxList[i]的Node數
    // 有向圖：求 點c 的 Out-degree = vtxList[i]的Node數
    cnt = vtxList[idx].size;

    // 有向圖：求 點c 的 In-degree = 所有Node中 點c的出現次數
    if(dir == true){
        for(int i=1;i<=n;++i)
            if(vtxList[i].searchNode(x)) cnt++; 
    }

    return cnt;
}

void ALGraph::InsertVertex(int v){
    if(v <= n) return; // 點v 已存在
    else{
        if(n >= capacity-1){
            cout << "Full!" << endl; return;
        }
        else n++;    // Vertex 總數+1
    }
}
void ALGraph::InsertEdge(int u, int v, int w){
    int ui = u;
    int vi = v;

    // 若 點u & 點v 都存在，且不相等
    if(ui>0 && vi>0 && !(ui==vi)){
        if(dir == false){
            if(!vtxList[ui].searchNode(v) && !vtxList[vi].searchNode(u)){
                vtxList[ui].insertBack(v,w);
                vtxList[vi].insertBack(u,w);
                e++;    // Edge 總數+1  
            }
        }
        else {
            vtxList[ui].insertBack(v,w);
            e++;    // Edge 總數+1
        }

    }
}
void ALGraph::DeleteVertex(int v){
    int del = v;
     if(del <= 0 || del > n){
        cout << "Vertex " << v << " doesn't exist." << endl;
        return;
    }

    // 統計 要減去的 Edge數量(因為 點v 消失，減少的邊)
    int cnt = vtxDegree(v);

    // free 掉 Vertex[i] 所接的 List
    vtxList[del].deleteList();

    // 將 Vertex[i] 後方的元素 往前搬一格
    for(int i=del;i<=n;i++)
        vtxList[i] = vtxList[i+1];

    n--;    // Vertex 總數-1

    // 將 Vertex[i]，包含 點v 的 Node 刪去
    for(int i=1;i<=n;i++)
        vtxList[i].deleteNode(v);

    e = e-cnt; // Edge 總數- 點v的Degree(邊數)
}
void ALGraph::DeleteEdge(int u, int v){
    int ui = u;
    int vi = v;

    if(ui <= 0 || vi <= 0) return; // Edge(u,v) 不存在

    if(dir == false){
        vtxList[ui].deleteNode(v);
        vtxList[vi].deleteNode(u);
    }
    else vtxList[ui].deleteNode(v);

    e--;    // Edge 總數-1
}

// Output
void ALGraph::printList(){
    cout << "Adjacency List (n=" << n << ",e=" << e <<")"; 
    cout << endl;
    for(int i=1;i<=n;++i){
        cout << i << ":\t";
        vtxList[i].printList();
    }
}

// MST 
void ALGraph::printMST(int *parent,int *minCost, int mstIdx, int mstSum){
    cout << "# Edge:" << mstIdx-1 << "\t Cost:" << mstSum <<endl;
    for(int i=1;i<=n;++i){
        if(parent[i]>0){
            cout << parent[i] << "," << i << "(" << minCost[i] <<")" <<endl;
        }
    }
}
int ALGraph::MST_Prim(int s){
    VertexHeap vtxHeap(n);   // 用一個 Heap 去存「頂點」的「周圍邊 最小成本」

    int* minCost = new int[n+1];    // 儲存 頂點的「周圍邊 最小成本」
    int* parent = new int[n+1];     // 儲存 頂點的父點(路徑)
    int* MSTvtx = new int[n+1];     // 儲存 已收入 MST 的頂點(1:已收入/0:未收入)
    // 初始化 
    for(int i=0;i<=n;++i){
        minCost[i]=999; // 頂點的周圍邊成本，初始化=999
        parent[i]=-1; 
        MSTvtx[i]=0;     
    }
    int mstIdx=0, mstSum=0;

    // Phase 1：Heap Push()
    minCost[s]=0;       // 起點s 的權值 = 0(最先被 Pop出來，並尋找 周圍最小邊)
    VHeapNode tempVtx;
    for(int i=1;i<=n;++i){
        tempVtx.no = i;
        tempVtx.cost = minCost[i];
        vtxHeap.Push(tempVtx);
    }

    // Phase 2：當 Heap 為空，表示 Spanning Tree 繪製完成
    while(!vtxHeap.isEmpty()){
        // Phase 2-1：從 Heap Pop出最小值(有「最小成本邊」的 點u)
        vtxHeap.Pop(tempVtx);  

        // Phase 2-2：找出 所有 該點u 的鄰近點v
        // 並將「周圍最小邊(u,v)」的成本 存入 minCost[v]，並更新 parent[v]=u
        // 注意：此處會更新 Heap 中，所存頂點之「周圍邊 最小成本」
        Vertex* current = vtxList[tempVtx.no].first;    // cur指向 點u List的首節點
        while(current){
            int curIdx = vtxHeap.findPos(current->no);  // curIdx 是 鄰點v 在 Heap中的位置
            // 若 鄰點v 原成本 > 邊(u,v)的成本 且 鄰點v 未被收入到MST中 -> 更新 鄰點v 資訊
            if((minCost[current->no] > current->weight) && MSTvtx[current->no]==0){
                parent[current->no] = tempVtx.no;           // v.parent = u
                minCost[current->no] = current->weight;     // v.cost = (u,v)成本
                vtxHeap.heap[curIdx].cost = current->weight;// 更新 heap中 點v 的成本

                vtxHeap.adjustUp(curIdx);   // 以 鄰點v 為起點，上浮調整 Heap
            }
            current = current->next;
        }

        MSTvtx[tempVtx.no] = 1;         // 並將該邊 收入 MST中
        mstSum += minCost[tempVtx.no];  // 累計「最小成本」
        mstIdx++;
    }

    printMST(parent,minCost,mstIdx,mstSum);
    delete[] minCost; delete[] parent; delete[] MSTvtx;
    return mstSum;
}

#endif

