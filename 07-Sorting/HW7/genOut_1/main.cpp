#include <iostream>
#include <cstdlib>
#include "myfile.hpp"
#include "search.hpp"
#include "sorting.hpp"
using namespace std;

/*
v	1. Selection Sort
v	2. Insertion Sort
v	3. Heap Sort
v	4. Merge Sort
v	5. Quick Sort
v	6. Radix Sort
v	7. qsort() in C library #inculde <cstdlib>
v	8. sort( ) in C++ std
*/

struct Arr{
    int *a;
    int size;
    int n;
    void setArr(int s){
        a = new int[s];
        size = s;
        n = size-1;
        for(int i=0;i<n;++i) a[i]=0;
    }
};

struct Filename{
    char *name;
    int length;
    void setNum(int n){
        length = n;
        // 求最大位數d
        int d = 1;
        int ntemp = n;
        while(ntemp/10 != 0){
            ntemp /= 10; ++d;
        }
        name = new char[1+d];
        sprintf(name,"%d",n);
    }
};

// 驗證一下獨讀到的資料
void printArr(int *a, int n){
    cout << "\n" << n <<":"<<endl;
    for(int i=1;i<=n;i++){
        cout << a[i] <<",";
        if(!((i+1)%25)) cout << endl;
    }
    cout << endl;
}

int main(){

    // Set input filename
    Filename fileNum[8];
    int hd=100, fhd=500;
    for(int i=0;i<8;i+=2){
        fileNum[i].setNum(hd);
        fileNum[i+1].setNum(fhd);
        hd*=10; fhd*=10;
    }

    FILE *fptr, *optr;

    for(int q=0;q<8;++q){

        // Create Input/Output Path
        char *ipath;
        ipath = new char[22+fileNum[q].length];
        sprintf(ipath,"/Users/jonaswu/cfile/input%s.txt",fileNum[q].name);
        // cout << ipath;

        char *opath;
        opath = new char[22+fileNum[q].length];
        sprintf(opath,"/Users/jonaswu/cfile/output%s.txt",fileNum[q].name);
        // cout << opath;
        
        fptr = fopen(ipath,"r");
        optr = fopen(opath,"w+");
        if(fptr == NULL) cout << ipath << " doesn't exist." <<endl;
        else{
            Arr arr;
            int n=0;

            rewind(fptr);
            fscanf(fptr,"%d",&n);
            arr.setArr(n+1);
            for(int i=1;i<=arr.n;i++){
                fscanf(fptr,"%d\n",&arr.a[i]);
            }

            // printArr(arr.a,arr.n);

            // selectionSort(arr.a,arr.n);
            // insertionSort(arr.a,arr.n);
            // heapSort(arr.a,arr.n);
            // rMergeSort(arr.a,1,arr.n);
            // quickSort(arr.a,1,arr.n);
            // radixSort(arr.a,10,arr.n);
            // qsort(arr.a,n+1,sizeof(int),compare);
            sort(arr.a,arr.a+n+1);

            // printArr(arr.a,arr.n);

            wirteIntArr(optr,arr.a,1,arr.n);
            
            delete[] arr.a;
        }
        
        fclose(fptr); 
        delete[] ipath;
        fclose(optr);
        delete[] opath;
        
        cout << q <<",";
    }
}
