#include "match.h"

int indexBruteforce(string &s, string &p) {
    int sI = 0;
    int pI = 0;

    while (sI < s.size() && pI < p.size()) {
        if (s[sI] == p[pI]) {
            sI++;
            pI++;
        }
        else {
            sI = sI - pI + 1;
            pI = 0;
        }
    }

    if (pI >= p.size())
        return sI - p.size();
    else
        return -1;
}

void getNext(string& p, int* N){
    int q=1;
    int k=0;
    N[0] = -1;
    while(q < p.size()){
        if(p[q]==p[k]){
            k++;
            N[q+1]=k;
            q++;
        }
        else if(k<=0){
            q++;
            N[q+1]=k;
        }
        else{
            k = N[k];
        }
    }
}

int indexKMP(string &s, string &p) {
    int sI = 0;
    int pI = 0;
    
    //配置一個 Next table
    unsigned int pLength = p.size();
    int *N = new int[pLength];
    for(int i=0;i<pLength;++i) N[i]=0;
    getNext(p,N);

    while (sI < s.size() && pI < p.size()) {
        if (s[sI] == p[pI] || pI == -1) {
            sI++;
            pI++;
        }
        //與暴力法的不同之處
        else pI = N[pI];
    }

    if (pI >= p.size())
        return sI - p.size();
    else
        return -1;
}