#include <iostream>
//#include "template_sll.hpp"
using namespace std;

int Max(int a,int b){return a>=b?a:b;}

struct Triple{
    int row, col, value;
};
ostream& operator<<(ostream& os, Triple& t){
    os << "(" << t.row <<","<< t.col <<","<< t.value <<")";
    return os;
}

class Matrix;

class MatrixNode{
    friend class Matrix;
    friend istream& operator>>(istream&, Matrix&);
    friend ostream& operator<<(ostream&, Matrix&);

    public:
        MatrixNode(bool h,Triple *tri){
            head = h;
            if(head) {right = down = data.next = this;}
            else data.triple = *tri;
        }
    private:
        MatrixNode *down, *right;
        bool head;
        union Data{
            MatrixNode* next;
            Triple triple;
        }data;
};

class Matrix{
    friend istream& operator>>(istream&, Matrix&);
    friend ostream& operator<<(ostream&, Matrix&);

    public:
        ~Matrix();
    private:
        MatrixNode *entryNode;
};

istream& operator>>(istream& is, Matrix& matrix){
    //第一階段：前置作業
    Triple entry;
    is >> entry.row >> entry.col >> entry.value;
    int n = Max(entry.row,entry.col);
    matrix.entryNode = new MatrixNode(false,&entry);
    
    if(!n){ cout<<"at least one row or column"<<endl; return is;}

    MatrixNode **head = new MatrixNode*[n];
    for(int i=0;i<n;++i)
        head[i] = new MatrixNode(true,0);

    int currentRow=0;
    MatrixNode *lastNode = head[0];

    //第二階段：依序讀入 Triples (假設Triple依照row號、col號由小到大排列)
    for(int i=0;i<entry.value;++i){
        Triple t;
        is >> t.row >> t.col >> t.value;
        MatrixNode* newNode = new MatrixNode(false,&t);

        if(t.row > currentRow){
            lastNode->right = head[currentRow]; //將 lastNode 與head[row]繞成一圈
            currentRow = t.row;
            lastNode = head[currentRow];
        }
        lastNode->right = newNode;
        lastNode = newNode;
        // 以上也可以寫成 lastNode = lastNode->right = newNode;
        // 執行順序：先執行右邊等號，在執行左邊等號

        //借用一下 head[t.col]的next 來儲存上次在t.col新增的Tirple
        head[t.col]->data.next->down = lastNode;// 將上次在t.col新增的Tirple的down 指向 這次新增的Triple
        head[t.col]->data.next = lastNode;      // 更新 head[t.col]的next 來儲存 這次新增的Triple
    } 
    // 第三階段：收尾 
    // 將最後一列的 lastNode 與head[row]繞成一圈
    lastNode->right = head[currentRow];
    // 將 每一行的 Node 與head[col] 繞成一圈
    for(int i=0;i<n;++i) head[i]->data.next->down = head[i];
    // 將 head[i] 串起來
    for(int i=0;i<n-1;++i) head[i]->data.next=head[i+1];
    head[n-1]->data.next = matrix.entryNode;
    matrix.entryNode->right = head[0];
    delete []head;
    return is;
}

Matrix::~Matrix(){
    if(!entryNode) return;
    MatrixNode *currentRow = entryNode->right; //current = head[0]
    MatrixNode *current;
    while(currentRow != entryNode){     //逐列刪除
        current = currentRow->right;    
        while(current != currentRow){   //每一列中，逐行刪除
            MatrixNode *delNode = current;
            current = current->right;
            delete delNode;
        }               
        currentRow = currentRow->data.next; //將 currentRow 指向 head[i+1]
        delete current;                     //將 head[i] 刪除
    }
    delete entryNode; entryNode=0;  //最後將 entryNode 刪除
}

ostream& operator<<(ostream& os, Matrix& matrix){
    if(!matrix.entryNode) return os;

    int Rows = matrix.entryNode->data.triple.row;
    int Cols = matrix.entryNode->data.triple.col;
    os << "\nMatrix:" << matrix.entryNode->data.triple << endl;

    int **array = new int*[Rows];
    for(int i=0;i<Rows;++i) array[i] = new int[Cols];

    for(int i=0;i<Rows;++i)
        for(int j=0;j<Cols;++j) array[i][j]=0;

    MatrixNode *currentRow = matrix.entryNode->right; //current = head[0]
    MatrixNode *current;

    while(currentRow != matrix.entryNode){
        current = currentRow->right;    // current 指向 row[0]右方第一個元素  
        while(current != currentRow){   //每一列中，逐行印出
            array[current->data.triple.row][current->data.triple.col] = current->data.triple.value;
            current = current->right;
        }
        current = currentRow;                 
        currentRow = currentRow->data.next; //將 currentRow 指向 head[i+1]
    }
    for(int i=0;i<Rows;++i){
         for(int j=0;j<Cols;++j) os << array[i][j] <<"\t";
         os << endl;
    }
    return os;
}


int main(void){
    Matrix matrix;
    cin >> matrix;
    cout << matrix;
}
