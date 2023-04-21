#ifndef _SORTING_HPP_
#define _SORTING_HPP_

#include <iostream>
#include "queue.hpp"
using namespace std;

/*
1.  Basic Sort
    1.  void insertionSort(T *a,int n)
    2.  void selectionSort(T *a,int n)
    3.  void bubbleSort(T *a,int n)
2.  Advance Sort
    1.1 void quickSort(T *a,int m,int n)
    1.2 void aQuickSort(T *a,int m,int n)
        a.  int partition(T *a,int m,int n)

    2.1 void iMergeSort(T *a,int n) 
        a.  void merge(T *a,T* ra,int l,int m,int n)
        b.  void mergePass(T *a,T *ra,int runlen,int n)
    2.2 int rMergeSort(T *a, int left,int right)
        a.  int listMerge(T *a, int p,int q, int n)

    3.  void heapSort(T *tree,int n)
        a.  void adjust(T *tree, int rIdx, int n)

3.  Linear-time Sort
    1.  void radixSort(T *a,int r,int n)
    2.  void countingSort(T *a, int r, int exp, int n)
    3.  void cRadixSort(T *a, int r, int n)
    4.  void bucketSort(T *a, int r, int n)

*/




/***** Basic function *****/
template <class T>
void swapT(T &a,T &b){
    T temp;
    temp = a;
    a = b;
    b = temp;
}

/***** List Sort(查表重排) *****/
template <class T>
void listRearrange(T *a,int *linka,int n,int first){
    //Phase 1：建立 linkb
    int *linkb = new int[n+1];
    for(int i=first; i!=0; i=linka[i])
        linkb[linka[i]] = i; //更新 a[i]下個元素的linkb = linkb[linka[i]]

    //Phase 2：更新a[i]成正確的Record
    for(int i=1; i<=n; ++i){
        // 把 first 當成 指向「正確Data」的游標，i 則是 指向「正要更新的位置」
        if(first != i){     //當游標指向的 Data = 正要更新的位置，表示該Data以安放在正確位置

            //注意1：一般要修改2個地方
            if(linka[i])    //1> 若a[i]有下個元素(linka[i]≠0)，要修改 下個Data的linkb
                linkb[linka[i]] = first;
            linka[linkb[i]] = first;    //2> 要修改 前個Data的linka
            swapT(a[i],a[first]);
            swapT(linka[i],linka[first]);
            swapT(linkb[i],linkb[first]);
        }
        first = linka[i];   //注意2：此時，a[i]已是正確資料，故將first指向下一筆正確資料的位置
    }
}

/***** Table Sort(查表重排) *****/
template <class T>
void tableRearrange(T *a,int *table,int n){
    for(int i=1;i<=n;++i){
        if(i != table[i]){
            a[0] = a[i];
            int j = i;
            do{
                int next = table[j];    //1> 記錄下個要造訪的位置
                a[j]=a[table[j]];       //2> 移動 Data 到正確位置
                table[j]=j;             //3> 更新table紀錄的index
                j = next;               //4> 將游標 移動到 下個正確的Data
            }while(table[j] != i);  //若table指示的位置 為 初始位置，則跳出回圈
            a[j] = a[0];
            table[j] = j;
        }
    }
    a[0]=0;
}

/*---------- Basic Sorting Method ----------*/

/***** Insertion sort *****/
template <class T>
void insert(T *a,T r,int i){
    int j=i;
    a[0] = r; //當a[j]抵達邊界a[0]，必然跳出while(r<a[j])迴圈
    while(r < a[j]){
        a[j+1]=a[j];
        --j;
    }
    a[j+1]=r;
}

template <class T>
void insertionSort(T *a,int n){
    for(int i=2;i<=n;++i){
        insert(a,a[i],i-1);
    }
}

/***** Selection sort *****/
template <class T>
void selectionSort(T *a,int n){
    int min; //指向最小值的Index
    for(int i=1;i<=n-1;++i){    //(n-1) Pass
        min = i;
        for(int j=i;j<=n;++j){  //找出 i~n 的min
            if(a[j] < a[min]) min=j;
        }
        if(i != min) swap(a[i],a[min]);
    }
}

/***** Bubble sort *****/
template <class T>
void bubbleSort(T *a,int n){
    for(int i=1;i<=n-1;++i){
        int swapFlag = 0;   //Flag表示 有無Swap產生
        for(int j=1;j<=n-i;++j){
            if(a[j]>a[j+1]){
                swapT(a[j],a[j+1]);
                swapFlag = 1;
            }
        }
        if(!swapFlag) return;
    }
}

/*---------- Advance Sorting Method ----------*/

/***** Quick sort *****/

// DS verion
template <class T>
void quickSort(T *a,int m,int n){
    if(m < n){  //注意1：m<n 才執行
        int i = m, j = n+1; //注意2：此處+1是因爲下方 do while 會先將 j-1
        do{
            do{
                i=i+1;
            }while(a[i] < a[m]); //a[i]>a[m]=Pivot時跳出，此時i指向>Pivot者
            do{
                j=j-1;
            }while(a[j] > a[m]); //a[j]<a[m]=Pivot時跳出，此時j指向<Pivot者
            if(i<j) swapT(a[j],a[i]); //交換間諜
        }while(i<j);       //注意3：當i=j重疊 或 i>j交錯，則跳出迴圈
        swapT(a[j],a[m]);   

        quickSort(a,m,j-1); //排序左半邊
        quickSort(a,j+1,n); //排序右半邊
    }
}

// Algo verion

template <class T>
int partition(T *a,int m,int n){
    int i=m-1, j=m;     // 游標j 指向 m，游標i 指向 j 的前一格
    for(j=m;j<=n-1;++j){
        // 設a[n]為Pivot，游標j找尋「 <Pivot的元素」，並往前交換(與i+1交換)
        if(a[j] <= a[n]){   
            i++;
            swapT(a[i],a[j]);
        }
    }
    swapT(a[n],a[i+1]); //搜尋結束，Pivot 與 a[i+1] 交換
    return (i+1);
}

template <class T>
void aQuickSort(T *a,int m,int n){
    if(m < n){  //注意1：m<n 才執行
        int p = partition(a,m,n);
        aQuickSort(a,m,p-1);
        aQuickSort(a,p+1,n);
    }
}

/***** Iterative Merge sort *****/
template <class T>
void merge(T *a,T* ra,int l,int m,int n){
    // Run 1(a[l]~a[m])、Run 2(a[m+1]~a[n])
    int p,q,i;  //p指向Run1、q指向Run2、i指向Result Array
    //注意1：i也是從l開始，因為merge函數，可能只處理某個 List 的一部份
    for(p = l, q = m+1, i = l; p<=m && q<=n ; ++i){
        if(a[p]<=a[q]){ 
            ra[i]=a[p];
            p=p+1;
        }
        else{
            ra[i]=a[q];
            q=q+1;
        }
    }
    while(p<=m){
        ra[i]=a[p];
        p++; i++;   //注意2：p & i 都要++
    }
    while(q<=n){
        ra[i]=a[q];
        q++; i++;
    }
}

template <class T>
void mergePass(T *a,T *ra,int runlen,int n){
    int i;
    // Merge 兩兩一組的Run
    for(i=1; i<=(n-2*runlen+1); i=i+2*runlen){
        merge(a,ra,i,i+runlen-1,i+2*runlen-1);
    }
    //若最後一組Run1長度≠Run2長度 -> 特別處理
    //Case 1：有Run2 -> Merge
    if(i+runlen-1 < n)  
        merge(a,ra,i,i+runlen-1,n); 
    //Case 2：只有Run1 -> Copy
    else{               
        while(i<=n){
            ra[i]=a[i]; i++;
        }
    }  
}

template <class T>
void iMergeSort(T *a,int n){
    T *temp = new T[n+1];
    //注意：i是指 每個Run的長度，從1->2->4->...
    for(int i=1;i<=(n/2);i=2*i){
        mergePass(a,temp,i,n);  //Pass 1 讓結果存在 temp 
        i=2*i; 
        mergePass(temp,a,i,n);  //Pass 2 讓結果存回 a
    }
    delete[] temp;
}

/***** Recursive Merge sort *****/

// Using Table Sort
template <class T>
int listMerge(T *a,int *t,int p,int q, int n){
    // Run 1(a[p]~a[q-1])、Run 2(a[q]~a[n])
    int r1=p,r2=q,i=p;
    int *temp = new int[n+1];       //注意1：「必須」使用 暫時table 存值
    while(r1<q && r2<=n){           //注意2：當r1、r2都沒有超出「該Run的邊界」時
        if(a[t[r1]]<=a[t[r2]]){     //注意3：採用Table Sort，需要「間接參考」
            temp[i]=t[r1];          //將「間接index」存入 暫時table
            r1++; i++;
        }
        else{
            temp[i]=t[r2];
            r2++; i++;
        }
    }
    while(r1<q){
        temp[i]=t[r1];
        r1++; i++;
    }
    while(r2<=n){
        temp[i]=t[r2];
        r2++; i++;
    }
    //注意3：Update table from temp
    for(int j=p;j<=n;j++) t[j]=temp[j];
    delete[] temp;
    return p;
}

template <class T>
int rMergeSort(T *a,int *t, int left,int right){
    if(left>=right) return left;          //終止條件1：切到剩自己，回傳自己

    int mid = (left+right)/2;             //注意：永遠分成兩半，直到切到剩自己
    int r1 = rMergeSort(a,t,left,mid);    //Merge Sort 左半
    int r2 = rMergeSort(a,t,mid+1,right); //Merge Sort 右半
    return listMerge(a,t,r1,r2,right);    //終止條件2：合併左右兩半，回傳Run1開頭
}

// Simple ver.
template <class T>
void listMerge(T *a,int p,int q, int n){
    // Run 1(a[p]~a[q-1])、Run 2(a[q]~a[n])
    int r1=p, r2=q, idx=p;
    T *temp = new int[n+1];       //注意1：「必須」使用 ra 暫時存值

    while(r1<q && r2<=n){       //注意2：當r1、r2都沒有超出「該Run的邊界」時
        if(a[r1]<=a[r2]){ 
            temp[idx]=a[r1];
            r1++; idx++;
        }
        else{
            temp[idx]=a[r2];
            r2++; idx++;
        }
    }
    while(r1<q){    //Run1還有剩
        temp[idx]=a[r1]; r1++; idx++;
    }
    while(r2<=n){   //Run2還有剩
        temp[idx]=a[r2]; r2++; idx++;
    }
    // Update a from ra
    for(int j=p;j<=n;j++) a[j]=temp[j];   // 注意3：j=p 開始(從0複製，會蓋掉a[]的原值)
    delete[] temp;
}

template <class T>
void rMergeSort(T *a,int m,int n){

    int mid = (m+n)/2;       //注意1：永遠分成兩半，直到切到剩自己

    if(m < n){       // 注意2：不含「＝」，2元素要「分開」才需合併  
        rMergeSort(a, m, mid);          //Merge Sort 左半
        rMergeSort(a, mid+1, n);        //Merge Sort 右半
        listMerge(a, m, mid+1, n);      //合併左右兩半
    }
}

/***** Heap Sort *****/

//Build Heap...
template <class T>
void adjust(T *tree, int rIdx, int n){
    int current = rIdx;
    int maxChild = 2*current;  //令maxChild指向current左孩

    T subroot = tree[current]; //暫存tree[rIdx]
    //當 current 沉到最底，maxChild 必然超過 n -> maxChild≤n 表示孩子存在
    while(maxChild <= n){
        //注意1：若 maxChild=n 表示current僅有一左子，若 maxChild<n 表示還有「右子」
        if(maxChild < n)
            //current有右子，才比較 current 兩孩的大小(不然會比到其他人的孩子)
            if(tree[maxChild] < tree[maxChild+1]) maxChild = maxChild+1;

        //若 current的值=subroot 比孩子小，則下沉
        if(subroot < tree[maxChild]){   //注意2：要用暫存的subroot值去比較！！
            tree[current] = tree[maxChild];
            current = maxChild;
            maxChild = 2*current;
        }
        else break;
    }    
    tree[current] = subroot;
}

//Heap Sort...
template <class T>
void heapSort(T *tree,int n){
    //Phase 1：Build Heap
    for(int i=n/2; i>=1; --i) adjust(tree,i,n);

    //Phase 2：Pop & Sort
    for(int i=n-1; i>=1; --i){
        swap(tree[i+1],tree[1]);
        adjust(tree,1,i);
    }
}

/*---------- Linear-time Sorting Method ----------*/
// pow(a,n)
int pow(int a,int n){
    int ans = 1;
    for(int i=1;i<=n;++i) ans *= a;
    return ans;
}

// getMax(a,n)
template <class T>
int getMax(T *a,int n){
    T max = a[1];
    for(int i=1;i<=n;++i)
        if(max < a[i]) max = a[i];
    return max;
}

/***** Radix Sort (LSD) *****/
template <class T>
void radixSort(T *a,int r,int n){
    // Build Bucket (以r=10進位為例)
    // (陣列實作 需要10倍空間(0~9)，因為最差的情況，一個桶子要放n筆資料)
    Queue<int> **bucket = new Queue<int>*[r];
    for(int i=0; i<r; i++){
        bucket[i] = new Queue<int>(n);
    }

    // 求最大位數d
    int max = getMax(a,n);
    int d = 1;
    while(max/10 != 0){
        max /= 10;
        ++d;
    }
    
    // Radix Sort
    for(int i=0; i<d; ++i){   //從第1位數～第d位數
        // Phase 1：分派
        for(int j=1; j<=n; ++j){  //取出每個元素的 第i位數 存入對應桶子
            int digit = (a[j]/pow(r,i)) % r;
            bucket[digit]->Push(a[j]);
        }
        // Phase 2：合併
        int idx=1;
        for(int k=0; k<r; ++k){  //從0~9號桶子 依序Pop存回 陣列a
            while(!bucket[k]->isEmpty()){
                bucket[k]->Pop(a[idx]);
                idx++;
            }
        }
    }
    // free memory
    for(int i=0; i<r; i++)
        delete[] bucket[i];
    delete[] bucket;
}

/***** Counting Sort (0~r-1) *****/
//評語：只能排列 有限範圍的Data，當Data數量少 但上下限廣 ex.[1,999] 就很浪費空間
template <class T>
void countingSort(T *a, int r, int exp, int n){
    //注意1：Build temp array 為必要花費空間
    T *ar = new T[n+1];
    for(int i=1;i<=n;++i) ar[i]=a[i];

    //1> Build count
    int *count = new int[r];
    for(int i=0;i<r;++i) count[i]=0;

    for(int i=1;i<=n;++i) count[ (ar[i]/pow(r,exp))%r ]++;
    //注意2：排序是以 a[i]的「第(exp+1)個位數」為基準

    //2> Build start
    int *start = new int[r];
    for(int i=0;i<r;++i) start[i]=0;

    start[0]=1;
    for(int i=1;i<=r;++i) start[i]=start[i-1]+count[i-1];

    //Counting Sort
    for(int i=1;i<=n;++i){
        int digit = (ar[i]/pow(r,exp))%r;
        a[ start[digit] ] = ar[i];
        start[digit]++;
        //注意2：排序是以 a[i]的「第(exp+1)個位數」為基準
    }
    delete[] count; delete[] start; delete[] ar;
}

/***** Radix Sort (LSD) with countingSort *****/
template <class T>
void cRadixSort(T *a, int r, int n){
    // 求最大位數d
    int max = getMax(a,n);
    int d = 1;
    while(max/10 != 0){
        max /= 10;
        ++d;
    }
    //從第1位數～第d位數，共執行 d個 Pass
    for(int i=0; i<d; ++i)   
        countingSort(a,r,i,n); //依照 陣列a的 第(i+1)個位數 排列
}

/***** Radix Sort (MSD) aka Bucket Sort *****/
//評語：若位數差異很大 [1,3,5,8,6,999]，那基本上時間都花在 桶中排序(InsertionSort)
template <class T>
void bucketSort(T *a, int r, int n){

    // Build bucket
    T **bucket = new T*[r];
    for(int i=0;i<r;++i)
        bucket[i] = new T[n+1]; //bucket[i][0] 不放資料
    
    int *top = new int[r]; // top[i] 指標 指向 bucket[i] 頂端
    for(int i=0;i<r;++i) top[i]=0;
        
    // 求最大位數d
    int max = getMax(a,n);
    int d = 1;
    while(max/10 != 0){
        max /= 10;
        ++d;
    }
    
    // Phase 1 分派
    for(int i=1;i<=n;++i){
        int digit = (a[i]/pow(r,d-1))%r;
        top[digit]++;
        bucket[digit][top[digit]] = a[i];
    }
    // Phase 2 排序
    for(int i=0;i<r;++i) //從0號桶～(r-1)號桶 逐一排序
        insertionSort(bucket[i],top[i]);

    // Phase 3 合併
    int k=1;
    for(int i=0;i<r;++i) //從0號桶～(r-1)號桶 依序存回 陣列a
        for(int j=1;j<=top[i];++j){
            a[k] = bucket[i][j];
            k++;
        }
}

#endif
