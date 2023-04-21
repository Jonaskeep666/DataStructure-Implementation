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

class Set{
    friend class ALGraph;
    public:
        Set(int c){
            n = c;
            subset = new int[c];
            for(int i=0;i<c;i++)
                subset[i]=-1;
        }
        // Maintain
        int CollapseFind(int x);    // 找 頂點x 的root (是屬於哪個集合)
        void Union(int u, int v);   // 將 頂點v 加入 頂點u 所在的集合

        // Output
        void printSet();
        // Build
        void buildSet(int Idx,int pa){ subset[Idx] = pa; }

    private:
        // 若(subset[i]>0) subset[i] 表示為「元素的父點」
        // 若(subset[i]<0) |subset[i]| 表示為「集合的元素個數」
        int* subset;    
        int n;
};

struct EdgeNode{
    void set(int s, int e, int w){
        weight = w; start = s; end = e;
    }
    int weight;
    int start;
    int end;
};
class EdgeHeap{
    friend class ALGraph;

    public:
        EdgeHeap(int e){
            capacity = e+1;
            heap = new EdgeNode[capacity];
            for(int i=0;i<capacity;++i)
                heap[i].set(-1,-1,0);
            size = 0;
        }
        bool isEmpty(){return size==0;}

        //access
        EdgeNode Top(){return heap[1];}

        //maintainance
        void Push(EdgeNode newNode);
        void Pop(EdgeNode& max);

        //operation
        void adjust(int rootIdx);
        void buildHeap();

    private:
        EdgeNode *heap;
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
        void printMST(EdgeNode *MST, int mstIdx, int mstSum);
        int MST_Kruskal();

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
// Set
int Set::CollapseFind(int x){
    int Idx = 0;

    // Phase 1：找根root，也就是「集合」的隊長
    // -> 若 Idx 的父點 存在(>=0)，則將 Idx 指向其父點
    // -> 若 Idx 的父點 不存在(<0)，表示 Idx 指向 root
    for(Idx = x; subset[Idx]>=0; Idx = subset[Idx]); 
    int root = Idx;

    // Phase 2：從 Idx = x 開始 往上更新 經過點的parent (改成指向root)，直到 Idx = root
    Idx = x;
    while(Idx!=root){
        int parent = subset[Idx];   // 暫存 Idx 的父點
        subset[Idx] = root;         // 將 Idx 改指向 root
        Idx = parent;               // 將 Idx 指向原父點
    }
    return root;
}
void Set::Union(int u, int v){
    // Union by height
    // 比較 Set(u) & Set(v) 的大小，小的指向大的
    int uRoot = CollapseFind(u);
    int vRoot = CollapseFind(v);

    if(ABS(subset[uRoot]) > ABS(subset[vRoot])){
        subset[uRoot] = subset[uRoot] + subset[vRoot];
        subset[vRoot] = uRoot;
    }
    else{
        subset[vRoot] = subset[uRoot] + subset[vRoot];
        subset[uRoot] = vRoot;
    }
}
void Set::printSet(){
    cout << "#" << setw(3) << "p" <<endl;
    for(int i=0;i<n;++i){
        cout << i <<":" << setw(2) << subset[i] << endl;
    }
}

// ---------------------------------------------------------------------------------------
// EdgeHeap

//maintainance
void EdgeHeap::Push(EdgeNode newNode){
    if(size == capacity){
        cout<<"Heap is full."<<endl;
        return;
    }

    size++;
    int newIndex = size;
    while(!(newIndex == 1) && (newNode.weight < heap[(newIndex)/2].weight)){
        heap[newIndex] = heap[(newIndex)/2]; //將Parent往下移動
        newIndex = newIndex/2;
    }
    heap[newIndex] = newNode; 
    
}
void EdgeHeap::Pop(EdgeNode& min){
    if(isEmpty()){ cout<<"Empty!"<<endl; return;}
    
    min = heap[1];
    heap[1] = heap[size];
    size--;
    adjust(1);
}

//operation
void EdgeHeap::adjust(int rootIdx){
    EdgeNode subroot = heap[rootIdx]; //暫存heap[rootIdx]
    int current = rootIdx;    //root = lastNode
    int minChild = current*2; //指向最小的孩子

    //當指向的孩子 沒有超出 heap的大小時，代表「還有子樹」
    while(minChild <= size){
        //比較 current 的兩個孩子 誰比較大，minChild指向小的孩子
        if(heap[minChild].weight > heap[minChild+1].weight && minChild < size){
            minChild++;
        }
        //若current已經 比 最小的孩子還小，則調整結束
        if(subroot.weight <= heap[minChild].weight) break; 

        heap[current] = heap[minChild]; //將小的孩子上浮
        current = minChild;             //將current下沉到「小的孩子」所在位置
        minChild = current*2;           //將minChild指向新的孩子的位置
    }
    heap[current] = subroot;
}
void EdgeHeap::buildHeap(){
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
void ALGraph::printMST(EdgeNode *MST, int mstIdx, int mstSum){
    cout << "# Edge:" << mstIdx << "\t Cost:" << mstSum <<endl;
    for(int i=0;i<n-1;++i){
        cout << MST[i].start << "," << MST[i].end << "(" << MST[i].weight << ")" <<endl;
    }
}
int ALGraph::MST_Kruskal(){
    Set connectSet(n);      // 儲存 哪些頂點抱成一圖(連通集合) -> 用來判別 Cycle是否存在
    EdgeHeap edgeHeap(e);   // 用一個 Heap 去存 邊的權值

    // MST集合，透過 1D陣列 儲存列為「最小生成樹」的邊
    EdgeNode *MST = new EdgeNode[n-1];
    int mstIdx = 0, mstSum = 0;

    // Phase 1：Heap Push()
    Vertex* current;
    EdgeNode tempEdge;
    for(int i=1;i<=n;++i){
        current = vtxList[i].first;
        while(current){
            if(current->no > i){    // 「無向圖」中，終點編號 > 起點編號 即是「不重複的邊」
                tempEdge.set(i,current->no,current->weight);
                edgeHeap.Push(tempEdge);
            }
            current = current->next;
        }
    }
    
    // Phase 2：判斷 加入邊(u,v) 是否會形成 Cycle，不會的邊 才加入 MST集合  
    while(!edgeHeap.isEmpty() && mstIdx < n-1){

        // 先拿最小的邊 看一下 加入MST 會不會形成Cycle
        tempEdge = edgeHeap.Top();  

        int uRoot = connectSet.CollapseFind(tempEdge.start);
        int vRoot = connectSet.CollapseFind(tempEdge.end);
        // 若 點u、點v 的集合「隊長不同」-> 不形成 Cycle -> 加入 MST集合
        if(uRoot!=vRoot){
            MST[mstIdx] = tempEdge;
            mstIdx++;                   // MST 收入的邊個數+1
            mstSum += tempEdge.weight;  // MST 的原成本 + 新加入邊的成本
            connectSet.Union(tempEdge.start,tempEdge.end); // 將(u,v)兩點 歸類為一團(連通集合)
        }
        edgeHeap.Pop(tempEdge); //將此邊(u,v)從Heap中移除
    }

    printMST(MST,mstIdx,mstSum);
    delete[] MST; 
    return mstSum;
}

#endif

