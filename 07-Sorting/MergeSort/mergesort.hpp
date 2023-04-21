#ifndef _MERGESORT_HPP_
#define _MERGESORT_HPP_

template <class T>
int listMerge(T* a,int *link,const int start1,const int start2){
    int lastResult = 0;
    for(int last1 = start1, last2 = start2; last1 && last2;){
        if(a[last1] <= a[last2]){
            link[lastResult] = last1; 
            lastResult = last1;
            last1 = link[last1]; //link[i]存著i的下一個元素位置
        }
        else{
            link[lastResult] = last2;
            lastResult = last2;
            last2 = link[last2]; //link[i]存著i的下一個元素位置
        }
        if(last1 == 0) link[lastResult]=last2;
        else link[lastResult]=last1;
    }
    return link[0]; //透過link[0]暫存 合併完成的List的開頭
}

template <class T>
int recurMergeSort(T* a,int *link,const int left,const int right){
    if(left >= right) return left;
    int mid = (left+right)/2;
    return listMerge(a,link,recurMergeSort(a,link,left,mid),recurMergeSort(a,link,mid+1,right));
}

#endif
