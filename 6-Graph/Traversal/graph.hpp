#ifndef _BST_H_
#define _BST_H_

#include <iostream>
#include <iomanip>
#include "stack.hpp"
#include "queue.hpp"
using namespace std;

// Adjacency Matrix
class AMGraph{
    public:
        AMGraph(int c, bool direction){
            AM = new int*[c];
            for(int i=0;i<c;i++){
                AM[i] = new int[c];
                for(int j=0;j<c;j++) AM[i][j]=0;
            }
            vtx = new char[c];
            for(int j=0;j<c;j++) vtx[j]=0;

            capacity = c;
            n=0; e=0;
            dir = direction;
        }
        bool IsEmpty(){ return n==0;}

        // Access
        int searchVtx(char c);              // 搜尋 點c 所在的index

        // Maintain
        int vtxDegree(char c);              // 計算 點c 的Degree

        void InsertVertex(char v);          // insert 點v
        void InsertEdge(char u, char v);    // insert Edge(u,v)
        void DeleteVertex(char v);          // Delete 點v & 相關的Edge
        void DeleteEdge(char u, char v);    // Delete Edge(u,v)

        //Traversal
        void visitHere(int idx);
        void DFS(char v);   // 由 點v 開始進行 DFS 走訪
        void BFS(char v);   // 由 點v 開始進行 BFS 走訪

        // Output
        void printMatrix();

    private:
        int **AM;       // 相鄰矩陣
        char *vtx;      // Vertex 矩陣：紀錄 Vertex 的名稱 & 編號
        int capacity;   // 相鄰矩陣 的「最大」大小
        int n;          // Vertex 總數
        int e;          // Edge 總數
        bool dir;       // T:有向圖 F:無向圖
};

// ---------------------------------------------------------------------------------------
// AMGraph

// Access
int AMGraph::searchVtx(char c){
    for(int i=0;i<n;i++)
        if(vtx[i]==c) return i;
    return -1;
}

// Maintain

int AMGraph::vtxDegree(char c){
    int idx = searchVtx(c);
    int cnt = 0;
    if(idx < 0) return -1;

    // 若為 無向圖：算 該列和
    if(dir == false){
        for(int i=0;i<n;i++)
            cnt += AM[idx][i];
    }
    // 若為 有向圖：算 行列和
    else{
        for(int i=0;i<n;i++){
            cnt += AM[idx][i];
            cnt += AM[i][idx];
            // 無需減去重疊處
            // 因為 對角線 = 0
        }
    }
    return cnt;
}

void AMGraph::InsertVertex(char v){
     // 若 點v 不存在
    if(searchVtx(v)>=0) return;

    if(n >= capacity-1){
        cout << "Full!" << endl; return;
    }
    else{
        n++;    // Vertex 總數+1
        // 設定 vtx 編號(n-1) 的名稱 = v
        vtx[n-1] = v;   

        // 初始化 AM[n-1][i] & AM[i][n-1]
        // 因為 第n個Vertex，存在 vtx[n-1]
        // 其中 vtx[0]是第一點
        for(int i=0;i<n;i++){
            AM[n-1][i] = 0;
            AM[i][n-1] = 0;
        }
    }
}
void AMGraph::InsertEdge(char u, char v){
    int ui = searchVtx(u);
    int vi = searchVtx(v);

    // 若 點u & 點v 都存在，且不相等
    if(ui>=0 && vi>=0 && !(ui==vi)){
        if(dir == false){
            if(AM[vi][ui]==0 && AM[ui][vi]==0){
                AM[ui][vi] = 1;
                AM[vi][ui] = 1;
                e++;    // Edge 總數+1
            }
        }
        else{
            AM[ui][vi] = 1;
            e++;    // Edge 總數+1
        }   
    }
    return;
}
void AMGraph::DeleteVertex(char v){
    int del = searchVtx(v);
    // 若 點v 不存在
    if(del < 0) return;

    // 統計 要減去的 Edge數量
    // (因為 點v 消失，減少的邊)
    int cnt = vtxDegree(v);

    // 將 AM[del][i] = 第 del 列 以後的元素 往上搬一格
    for(int i=del;i<n;i++)
        for(int j=0;j<n;j++)
            AM[i][j]=AM[i+1][j];
    // 將 AM[i][del] = 第 del 行 以後的元素 往左搬一格
    for(int i=del;i<n;i++)
        for(int j=0;j<n;j++)
            AM[j][i]=AM[j][i+1];

    // 在 Vertex 陣列中，刪去 Vertex v，並將後方元素往前移動一格
    for(int i=del;i<n;i++)
        vtx[i]=vtx[i+1];

    n--;    // Vertex 總數-1
    e = e-cnt; // Edge 總數- 點v的Degree(邊數)
}
void AMGraph::DeleteEdge(char u, char v){
    int ui = searchVtx(u);
    int vi = searchVtx(v);

    // 若 Edge(u,v) 不存在
    if(ui < 0 || vi < 0) return;

    if(dir == false){
        AM[ui][vi] = 0;
        AM[vi][ui] = 0;
    }
    else AM[ui][vi] = 0;
    
    e--;    // Edge 總數-1
}

// Traversal
void AMGraph::visitHere(int idx){
    cout << vtx[idx] << ",";
}

void AMGraph::DFS(char v){
    Stack<int> stack(capacity);
    int *visit = new int[n];
    for(int i=0;i<n;++i) visit[i]=0;

    int vi = searchVtx(v);

    // Phase 1：先拜訪 起點v，並將 visit[vi] 設為已拜訪(=1) & Push
    visitHere(vi);
    visit[vi]=1;
    stack.Push(vi);

    // Phase 2：當 stack 為空，表示 所有的點 皆以拜訪完畢
    while(!stack.isEmpty()){
        vi = stack.Top();

        // Phase 2-1：找 點v 未拜訪的鄰近點
        // 其中，點v的鄰近點：(A[vi][i] == 1)時 的 i值
        for(int i=0;i<n;++i){
            // 找到 未拜訪的鄰近點i -> 拜訪 & Push
            if(AM[vi][i]==1 && visit[i]==0){
                visitHere(i);
                visit[i]=1;
                stack.Push(i);
                break;
            }
        }
        // Phase 2-2：若 點v「沒有」未拜訪的鄰近點(沒有 新點 被Push到stack)
        // -> 則 Pop先前拜訪的點，並試著尋找其 未拜訪鄰近點
        if(vi == stack.Top())
            stack.Pop(vi);
    }
}

void AMGraph::BFS(char v){
    Queue<int> queue(capacity);
    int *visit = new int[n];
    for(int i=0;i<n;++i) visit[i]=0;

    int vi = searchVtx(v);

    // Phase 1：先拜訪 起點v，並將 visit[vi] 設為已拜訪(=1) & Push
    visitHere(vi);
    visit[vi]=1;
    queue.Push(vi);

    // Phase 2：當 queue 為空，表示 所有的點 皆以拜訪完畢
    while(!queue.isEmpty()){
        queue.Pop(vi);
        // Phase 2-1：找 點v 「所有」未拜訪的鄰近點
        for(int i=0;i<n;++i){
            // 找到 未拜訪的鄰近點i -> 拜訪 & Push
            if(AM[vi][i]==1 && visit[i]==0){
                visitHere(i);
                visit[i]=1;
                queue.Push(i);
            }
        }
    }
}

// Output

void AMGraph::printMatrix(){
    if(IsEmpty()){
        cout << "Empty!" << endl;
        return;
    }
    cout << "Adjacency Matrix (n=" << n << ",e=" << e <<")"; 
    cout << endl;
    cout << "  ";
    for(int i=0;i<n;i++){
        cout << setw(2) << vtx[i] << ",";
    }
    cout << endl;
    for(int i=0;i<n;i++){
        cout << setw(2) << vtx[i] << "";
        for(int j=0;j<n;j++){
            cout << setw(2) << AM[i][j] << ",";
        }
        cout << endl;
    }
}

// ---------------------------------------------------------------------------------------
// Adjacency List

struct Vertex{
    void setVtx(char na){
        name = na; next = 0;
    }
    char name;
    Vertex* next;
};

class ALGraph;

class List{
    friend class ALGraph;

    public:
        List(){first=rear=0; size=0; name=0;}
        // Access
        Vertex* searchNode(char c); // 搜尋 Node(c) 的位址

        // Maintain
        Vertex* insertBack(char c); // 插入 Node(c) 到最後
        void deleteNode(char c);    // 刪除 Node(c)
        void deleteList();          // 刪除 整個List

        // Output
        void printList();

    private:
        Vertex* first; 
        Vertex* rear;
        char name;      // List 的名稱
        int size;       // List 的大小
}; 

class ALGraph{
    friend class List;

    public:
        ALGraph(int c, bool direction){
            vtxList = new List[c];
            for(int i=0;i<c;++i){
                vtxList[i].first = vtxList[i].rear = 0;
                vtxList[i].size = 0;
                vtxList[i].name = 0;
            }
            capacity = c;
            n=0; e=0;
            dir = direction;
        }
        bool IsEmpty(){ return n==0;}

        // Access
        int searchVtx(char c);      // 搜尋 點c 所在的index (of 相鄰串列)
        List* Adjacent(char c);     // 回傳 所有與點c 相鄰的點 形成的串列

        // Maintain
        int vtxDegree(char c);      // 計算 點c 的Degree

        void InsertVertex(char v);          // insert 點v
        void InsertEdge(char u, char v);    // insert Edge(u,v)
        void DeleteVertex(char v);          // Delete 點v & 相關的Edge
        void DeleteEdge(char u, char v);    // Delete Edge(u,v)

        //Traversal
        void visitHere(int idx);
        void DFS(char v);   // 由 點v 開始進行 DFS 走訪
        void BFS(char v);   // 由 點v 開始進行 BFS 走訪

        // Output
        void printList();

    private:
        List* vtxList;  // 相鄰串列
        int capacity;   // 相鄰串列 的「最大」大小
        int n;          // Vertex 總數
        int e;          // Edge 總數
        int dir;        // T:有向圖 F:無向圖
};

// ---------------------------------------------------------------------------------------
// List

// Access
Vertex* List::searchNode(char c){
    Vertex* current = first;
    if(first == 0) return 0;
    while(current){
        if(current->name == c) return current;
        current = current->next;
    }
    return 0;
}
// Maintain
Vertex* List::insertBack(char c){

    // 若 Vertex(c) 已存在，則退出
    if(searchNode(c)) return 0;

    Vertex* newNode = new Vertex;
    newNode->setVtx(c);

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
void List::deleteNode(char c){
    Vertex* delNode = searchNode(c);
    
    // 若 Vertex(c) 不存在，則退出
    if(delNode == 0){
        cout << "Vertex "<< c << " doexn't exist." <<endl;
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
        cout << current->name << ",";
        current = current->next;
    }
    cout << endl;
}

// ---------------------------------------------------------------------------------------
// ALGraph

// Access
int ALGraph::searchVtx(char c){
    for(int i=0;i<n;++i){
        if(vtxList[i].name == c) return i;
    }
    return -1;
}

// Maintain
int ALGraph::vtxDegree(char c){
    int idx = searchVtx(c);
    int cnt = 0;
    if(idx < 0) return -1;

    // 無向圖：求 點c 的 Degree = vtxList[i]的Node數
    // 有向圖：求 點c 的 Out-degree = vtxList[i]的Node數
    cnt = vtxList[idx].size;

    // 有向圖：求 點c 的 In-degree = 所有Node中 點c的出現次數
    if(dir == true){
        for(int i=0;i<n;++i)
            if(vtxList[i].searchNode(c)) cnt++; 
    }

    return cnt;
}

void ALGraph::InsertVertex(char v){
    if(searchVtx(v)>=0) return; // 點v 已存在
    else{
        if(n >= capacity-1){
            cout << "Full!" << endl; return;
        }
        else{
            n++;    // Vertex 總數+1
            vtxList[n-1].name = v;
        }
    }
}
void ALGraph::InsertEdge(char u, char v){
    int ui = searchVtx(u);
    int vi = searchVtx(v);

    // 若 點u & 點v 都存在，且不相等
    if(ui>=0 && vi>=0 && !(ui==vi)){
        if(dir == false){
            if(!vtxList[ui].searchNode(v) && !vtxList[vi].searchNode(u)){
                vtxList[ui].insertBack(v);
                vtxList[vi].insertBack(u);
                e++;    // Edge 總數+1
            }
        }
        else {
            vtxList[ui].insertBack(v);
            e++;    // Edge 總數+1
        }
    }
}
void ALGraph::DeleteVertex(char v){
    int del = searchVtx(v);
     if(del < 0){
        cout << "Vertex " << v << " doesn't exist." << endl;
        return;
    }

    // 統計 要減去的 Edge數量(因為 點v 消失，減少的邊)
    int cnt = vtxDegree(v);

    // free 掉 Vertex[i] 所接的 List
    vtxList[del].deleteList();

    // 將 Vertex[i] 後方的元素 往前搬一格
    for(int i=del;i<n;i++)
        vtxList[i] = vtxList[i+1];

    n--;    // Vertex 總數-1

    // 將 Vertex[i]，包含 點v 的 Node 刪去
    for(int i=0;i<n;i++)
        vtxList[i].deleteNode(v);

    e = e-cnt; // Edge 總數- 點v的Degree(邊數)
}
void ALGraph::DeleteEdge(char u, char v){
    int ui = searchVtx(u);
    int vi = searchVtx(v);

    if(ui < 0 || vi < 0) return; // Edge(u,v) 不存在

    if(dir == false){
        vtxList[ui].deleteNode(v);
        vtxList[vi].deleteNode(u);
    }
    else vtxList[ui].deleteNode(v);

    e--;    // Edge 總數-1
}

// Traversal
void ALGraph::visitHere(int idx){
    cout << vtxList[idx].name << ",";
}

void ALGraph::DFS(char v){
    Stack<int> stack(capacity);
    int *visit = new int[n];
    for(int i=0;i<n;++i) visit[i]=0;

    int vi = searchVtx(v);

    // Phase 1：先拜訪 起點v，並將 visit[vi] 設為已拜訪(=1) & Push
    visitHere(vi);
    visit[vi]=1;
    stack.Push(vi);

    // Phase 2：當 stack 為空，表示 所有的點 皆以拜訪完畢
    while(!stack.isEmpty()){
        vi = stack.Top();

        // Phase 2-1：找 點v 未拜訪的鄰近點
        // 其中，點v的鄰近點 = vtxList[vi] 後方的 Node
        Vertex* current = vtxList[vi].first;
        int cIdx = 0;
        while(current){
            cIdx = searchVtx(current->name);
            // 找到 未拜訪的鄰近點i -> 拜訪 & Push
            if(visit[cIdx]==0){
                visitHere(cIdx);
                visit[cIdx]=1;
                stack.Push(cIdx);
                break;
            }
            current = current->next;
        }
        // Phase 2-2：若 點v「沒有」未拜訪的鄰近點(沒有 新點 被Push到stack)
        // -> 則 Pop先前拜訪的點，並試著尋找其 未拜訪鄰近點
        if(vi == stack.Top())
            stack.Pop(vi);
    }
}

void ALGraph::BFS(char v){
    Queue<int> queue(capacity);
    int *visit = new int[n];
    for(int i=0;i<n;++i) visit[i]=0;

    int vi = searchVtx(v);

    // Phase 1：先拜訪 起點v，並將 visit[vi] 設為已拜訪(=1) & Push
    visitHere(vi);
    visit[vi]=1;
    queue.Push(vi);

    // Phase 2：當 queue 為空，表示 所有的點 皆以拜訪完畢
    while(!queue.isEmpty()){
        queue.Pop(vi);
        // Phase 2-1：找 點v 「所有」未拜訪的鄰近點
        Vertex* current = vtxList[vi].first;
        int cIdx = 0;
        while(current){
            cIdx = searchVtx(current->name);
            // 找到 未拜訪的鄰近點i -> 拜訪 & Push
            if(visit[cIdx]==0){
                visitHere(cIdx);
                visit[cIdx]=1;
                queue.Push(cIdx);
            }
            current = current->next;
        }
    }
}

// Output
void ALGraph::printList(){
    cout << "Adjacency List (n=" << n << ",e=" << e <<")"; 
    cout << endl;
    for(int i=0;i<n;++i){
        cout << vtxList[i].name << ":\t";
        vtxList[i].printList();
    }
}

#endif

