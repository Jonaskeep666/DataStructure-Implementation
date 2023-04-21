#include <iostream>
#include <cstdlib>
#include "myfile.hpp"
#include "search.hpp"
#include "sorting.hpp"
using namespace std;

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

struct SortingMethod{
    char *name;
    int no; //for output(no).txt
    SortingMethod(int no_){
        no = no_;
        switch (no){
            case 1:
                name = new char[15];
                sprintf(name,"Selection Sort"); //在文字黨中的註記
                break;
            case 2:
                name = new char[15];
                sprintf(name,"Insertion Sort");
                break;
            case 3:
                name = new char[15];
                sprintf(name,"Heap Sort");
                break;
            case 4:
                name = new char[15];
                sprintf(name,"Merge Sort");
                break;
            case 5:
                name = new char[15];
                sprintf(name,"Quick Sort");
                break;
            case 6:
                name = new char[15];
                sprintf(name,"Radix Sort");
                break;
            case 7:
                name = new char[15];
                sprintf(name,"qsort in C");
                break;
            case 8:
            default:
                name = new char[15];
                sprintf(name,"Sort in C++");
                break;
        }
        cout << name <<endl;
    }
    void Sort(int *a,int n,int start,int r){
            /*
        v	1. Selection Sort
                selectionSort(arr.a,arr.n);
        v	2. Insertion Sort
                insertionSort(arr.a,arr.n);
        v	3. Heap Sort
                heapSort(arr.a,arr.n);
        v	4. Merge Sort
                rMergeSort(arr.a,1,arr.n);
        v	5. Quick Sort
                quickSort(arr.a,1,arr.n);
        v	6. Radix Sort
                radixSort(arr.a,10,arr.n);
        v	7. qsort() in C library #inculde <cstdlib>
                qsort(arr.a,n+1,sizeof(int),compare);
        v	8. sort( ) in C++ std
                sort(arr.a,arr.a+n+1);
        */
        switch (no){
            case 1:
                selectionSort(a,n);
                break;
            case 2:
                insertionSort(a,n);
                break;
            case 3:
                heapSort(a,n);
                break;
            case 4:
                rMergeSort(a,start,n);
                break;
            case 5:
                quickSort(a,start,n);
                break;
            case 6:
                radixSort(a,r,n);
                break;
            case 7:
                qsort(a,n+1,sizeof(int),compare);
                break;
            case 8:
            default:
                sort(a,a+n+1);
                break;
        }
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
    // int q=0;
    for(int q=0;q<8;++q){
    
        // Create Input/Output Path
        char *ipath;
        ipath = new char[50+fileNum[0].length];
        sprintf(ipath,"/Users/jonaswu/cfile/input%s.txt",fileNum[0].name);
        // cout << ipath;

        char *opath;
        opath = new char[50];
        sprintf(opath,"/Users/jonaswu/cfile/output_%d.txt",(q+1));
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

            printArr(arr.a,arr.n);

            SortingMethod method(q+1);
            method.Sort(arr.a,arr.n,1,10);

            printArr(arr.a,arr.n);

            fprintf(optr,"%s\n",method.name);
            for(int i=1;i<=arr.n;i++)
                fprintf(optr,"%d\n",arr.a[i]);
            
            delete[] arr.a;
        }
        
        fclose(fptr); 
        delete[] ipath;
        fclose(optr);
        delete[] opath;
        
        cout << q <<",";
    }
}
