#include <iostream>
#include "heap.hpp"
using namespace std;

int main(){
    int num[10] = {3,19,6,7,31,13,94,38,52,48};

    MaxHeap<int> maxHeap(100),maxHeap2(100);
    HeapNode<int> a[10],max[10];
    HeapNode<int> temp;

    for(int i=0;i<10;++i){
        a[i].setNode(num[i],num[i]);
        cout << a[i] << ",";
    }
    cout << endl;
    cout << maxHeap.isEmpty() <<endl;

    for(int i=0;i<10;++i){
        maxHeap.Push(a[i]);
    }

    cout << maxHeap <<endl;
    cout << endl;

    //heapSort
    for(int i=0;i<10;++i){
        maxHeap.Pop(max[i]);
        cout << max[i] << ",";
    }
    cout << endl;
    cout << endl;

    //buildHeap
    for(int i=0;i<10;++i){
        maxHeap2.addItem(a[i]);
    }
    cout << maxHeap2 <<endl;
    cout << endl;

    maxHeap2.buildHeap();

    cout << maxHeap2 <<endl;
    cout << endl;


    //heapSort 2
    for(int i=0;i<10;++i){
        maxHeap2.Pop(max[i]);
        cout << max[i] << ",";
    }
    cout << endl;
    cout << endl;


}
