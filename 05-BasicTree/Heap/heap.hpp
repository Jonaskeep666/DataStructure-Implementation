#ifndef _HEAP_H_
#define _HEAP_H_

#include <iostream>
using namespace std;

template <class T> class HeapNode;
template <class T> class MaxHeap;
template <class T> ostream& operator<<(ostream& os, HeapNode<T>& node);
template <class T> ostream& operator<<(ostream& os, MaxHeap<T>& MHeap);

template <class T>
class HeapNode{
    friend class MaxHeap<T>;
    friend ostream& operator<< <T>(ostream& os, HeapNode<T>& node);
    public:
        HeapNode(){key=0;}
        HeapNode(int k){key=k;}
        HeapNode(T d,int k){data=d;key=k;}
        void setNode(T d,int k){data=d;key=k;}
    private:
        T data;
        int key;
};

template <class T>
ostream& operator<<(ostream& os, HeapNode<T>& node){
    os << "[" << node.data << "](" << node.key << ")";
    return os;
}

template <class T>
class MaxHeap{
    friend ostream& operator<< <T>(ostream& os, MaxHeap<T>& MHeap);
    public:
        MaxHeap(int);
        bool isEmpty(){return size==0;}

        //access
        HeapNode<T> Top(){return heap[1];}

        //maintainance
        void Push(HeapNode<T> newNode);
        void Pop(HeapNode<T>& max);

        //operation
        void adjust(int rootIdx);
        void buildHeap();
        void addItem(HeapNode<T> newNode);

    private:
        HeapNode<T> *heap;
        int size;
        int capacity;
};

template <class T>
ostream& operator<<(ostream& os, MaxHeap<T>& MHeap){
    int j=2;
    for(int i=1;i<=MHeap.size;++i){
        os << MHeap.heap[i] << ",";
        if(i==(j-1)){
            os<<"\n";
            j = j<<1;
        } 
    }
    return os;
}

template <class T>
MaxHeap<T>::MaxHeap(int _capacity){
    capacity = _capacity;
    heap = new HeapNode<T>[capacity + 1]; //heap[0] isn't used.
    size = 0;
}

//******maintainance******

template <class T>
void MaxHeap<T>::Push(HeapNode<T> newNode){
    if(size == capacity){
        cout<<"Heap is full."<<endl;
        return;
    }

    size++;
    int newIndex = size;
    while(!(newIndex == 1) && (newNode.key > heap[(newIndex)/2].key)){
        heap[newIndex] = heap[(newIndex)/2]; //將Parent往下移動
        newIndex = newIndex/2;
    }
    heap[newIndex] = newNode;  
}

template <class T>
void MaxHeap<T>::Pop(HeapNode<T>& max){
    if(isEmpty()){ cout<<"Empty!"<<endl; return;}
    
    max = heap[1];
    heap[1] = heap[size];
    size--;
    adjust(1);
    // HeapNode<T> subroot = heap[1]; //暫存heap[1]
    // int current = 1;               //root = lastNode
    // int maxChild = current*2;      //指向最大的孩子

    // //當指向的孩子 沒有超出 heap的大小時，代表「還有子樹」
    // while(maxChild <= size){
    //     //比較 current 的兩個孩子 誰比較大，maxChild指向大的孩子
    //     if(heap[maxChild].key < heap[maxChild+1].key && maxChild < size){
    //         maxChild++;
    //     }
    //     //若current已經 比 最大的孩子還大，則調整結束
    //     if(subroot.key >= heap[maxChild].key) break;   

    //     heap[current] = heap[maxChild]; //將大的孩子上浮
    //     current = maxChild;             //將current下沉到「大的孩子」所在位置
    //     maxChild = current*2;           //將maxChild指向新的孩子的位置
    // }
    // heap[current] = subroot;
}

template <class T>
void MaxHeap<T>::adjust(int rootIdx){
    HeapNode<T> subroot = heap[rootIdx]; //暫存heap[rootIdx]
    int current = rootIdx;    //root = lastNode
    int maxChild = current*2; //指向最大的孩子

    //當指向的孩子 沒有超出 heap的大小時，代表「還有子樹」
    while(maxChild <= size){
        //比較 current 的兩個孩子 誰比較大，maxChild指向大的孩子
        if(heap[maxChild].key < heap[maxChild+1].key && maxChild < size){
            maxChild++;
        }
        //若current已經 比 最大的孩子還大，則調整結束
        if(subroot.key >= heap[maxChild].key) break; 

        heap[current] = heap[maxChild]; //將大的孩子上浮
        current = maxChild;             //將current下沉到「大的孩子」所在位置
        maxChild = current*2;           //將maxChild指向新的孩子的位置
    }
    heap[current] = subroot;
}

template <class T>
void MaxHeap<T>::buildHeap(){
    for(int i=(size/2);i>=1;--i) 
        adjust(i);
}

template <class T>
void MaxHeap<T>::addItem(HeapNode<T> newNode){
    heap[size+1]=newNode;
    size++;
}

#endif
