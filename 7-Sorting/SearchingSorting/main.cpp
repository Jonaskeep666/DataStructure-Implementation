#include <iostream>
#include "search.hpp"
#include "sorting.hpp"
using namespace std;



int main(){
    int a[11]={0,26,5,77,1,61,11,59,15,48,19};
    int aa[11]={0,26,5,77,1,61,19,59,15,48,11};
    int c[9]={0,3,1,4,2,6,1,2,2};
    int ta[11]={0,1,2,3,4,5,6,7,8,9,10};
    // int linka[11]={0,9,6,0,2,3,8,5,10,7,1};

    // int b[8]={0,3,26,5,18,36,42,77},r[8]={0};

    // int list[9]={0,35,14,12,42,26,50,31,18};
    // int table[9]={0,3,2,8,5,7,1,4,6};

    // cout << seqSearch(a,sizeof(a)/sizeof(int)-1,77) <<endl;

    // insertionSort(a,sizeof(a)/sizeof(int)-1);
    // selectionSort(a,sizeof(a)/sizeof(int)-1);
    // bubbleSort(a,sizeof(a)/sizeof(int)-1);
    // quickSort(a,1,sizeof(a)/sizeof(int)-1);
    // aQuickSort(a,1,sizeof(a)/sizeof(int)-1);

    // iMergeSort(a,sizeof(a)/sizeof(int)-1);

    // rMergeSort(a,ta,1,sizeof(a)/sizeof(int)-1);
    // tableRearrange(a,ta,sizeof(a)/sizeof(int)-1);

    // rMergeSort(a,1,sizeof(a)/sizeof(int)-1);

    // radixSort(a,10,sizeof(a)/sizeof(int)-1);

    // countingSort(a,10,0,sizeof(a)/sizeof(int)-1);

    // cRadixSort(a,10,sizeof(a)/sizeof(int)-1);

    // bucketSort(aa,10,sizeof(a)/sizeof(int)-1);

    for(int i=0;i<11;++i)
        cout << a[i] <<",";
    cout << endl;
    rMergeSort(a,1,sizeof(a)/sizeof(int)-1);
    for(int i=0;i<11;++i)
        cout << a[i] <<",";
    cout << endl;


    // cout << pow(10,1) <<endl;

    // cout << iBinSearch(a,sizeof(a)/sizeof(int)-1,77) <<endl;
    // cout << rBinSearch(a,1,sizeof(a)/sizeof(int),77) <<endl;



    // table() test
    // tableRearrange(list,table,sizeof(list)/sizeof(int)-1);
    // for(int i=0;i<9;++i)
    //     cout << list[i] <<",";
    // cout << endl;

    // merge() test
    // for(int i=0;i<8;++i)
    //     cout << b[i] <<",";
    // cout << endl;
    // merge(b,r,1,2,7);
    // for(int i=0;i<8;++i)
    //     cout << r[i] <<",";
    // cout << endl;
    
}
