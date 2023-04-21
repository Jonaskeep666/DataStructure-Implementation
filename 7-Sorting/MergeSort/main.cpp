#include <iostream>
#include "mergesort.hpp"
using namespace std;



int main(){
    int a[11]={0,26,5,77,1,61,11,59,15,48,19};
    int link[11]={0};
    int start=0;


    start = recurMergeSort(a,link,1,10);
    cout << "\t";
    for(int i=1;i<=10;++i){
        cout << a[i] << ",\t";
    }
    cout << endl;
    for(int i=0;i<=10;++i){
        cout << link[i] << ",\t";
    }
    cout << endl;

    cout << "\t";
    for(int j=start;j!=0;){
        cout << a[j] << ",\t";
        j=link[j];
    }
    cout << endl;
}
