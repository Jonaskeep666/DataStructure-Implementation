#ifndef _SEARCH_HPP_
#define _SEARCH_HPP_

//資料從a[1]開始

template <class T>
int seqSearch(T *a,int n, T k){
    for(int i=1;i<=n;++i)
        if(a[i]==k) return i;
    return 0;
}

template <class T>
int iBinSearch(T *a,int n, T k){
    int left=1,right=n+1,mid;
    
    while(left <= right){
        mid = (left+right)/2;
        if(k > a[mid]) left = mid+1;
        else if(k < a[mid]) right = mid-1;
        else return mid;
    }
    return 0;
}

template <class T>
int rBinSearch(T *a,int left,int right, int k){
    if(left <= right){
        int mid = (left+right)/2;
        if(k > a[mid]) return rBinSearch(a,mid+1,right,k);
        else if(k < a[mid]) return rBinSearch(a,left,mid-1,k);
        else return mid;
    }
    else return 0;
}


#endif
