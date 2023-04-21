#ifndef _DHASH_HPP_
#define _DHASH_HPP_

#include <iostream>
using namespace std;

int twoExp(int n){
    int exp=1;
    for(int i=0;i<n;++i) exp *= 2;
    return exp;
}

void printBits(unsigned int num,int t){
    for(int i=(t-1);i>=0;--i){
        if(num & 1<<i) cout << '1';
        else cout << '0';
    }
    cout << endl;
}

struct Bucket{
    int slot[2];
    void clear(){
        slot[0]=-1; slot[1]=-1;
    }
    bool isFull(){ return (slot[0] >=0 && slot[1] >=0); }
    bool isEmpty(){return (slot[0] < 0 && slot[1] < 0); }
    void push(int data){
        if(isFull()){cout << "Bucket full!!" << endl; return;}
        else if(isEmpty()) slot[0]=data;
        else if(slot[1]==-1) slot[1]=data;
    }
};

ostream& operator<<(ostream& os, Bucket* bucket){
    if(bucket){
        if(bucket->slot[0]==-1) os << "[__]-";
        else os << "[" << bucket->slot[0] << "]-";
        if(bucket->slot[1]==-1) os << "[__]";
        else os << "[" << bucket->slot[1] << "]";
    }
    else os << "NULL";
    return os;
}

class DHash{
    public:
        DHash(int t_){
            t = t_;
            int size = twoExp(t_);
            Dr = new Bucket*[size];
            for(int i=0;i<size;++i)
                Dr[i]=0;
        }
        // Hash function：取(x)的前(t_)個位元 作為「Bucket位置」
        int func(int x,int t_);

        // 擴增目錄至深度(t_)，並初始化目錄指標
        // 包含指向舊Bucket，並將涉及Overflow的目錄 指向新增的bucket
        void reSizeDr(int t_,int overPos);

        void insert(int data);

        void printDhash();
    private:
        Bucket** Dr;    //指向目錄的指標
        int t;          //目錄深度
};

void DHash::reSizeDr(int t_,int overPos){
    int newSize = twoExp(t_);
    int oldSize = twoExp(t);
    
    // Step 1：新增 擴增目錄，並將 新目錄 指向 舊的Bucket
    Bucket** extDr = new Bucket*[newSize];
    for(int i=0;i<oldSize;++i){
        extDr[i] = Dr[i];
        extDr[i+oldSize] = Dr[i];
    }
    // Step 2：刪除舊目錄，並將 Dr指向 新 擴增目錄
    delete[] Dr;
    Dr = extDr;

    //  Step 3：將涉及Overflow的目錄 指向新增的bucket
    Dr[oldSize + overPos]= new Bucket;
    Dr[oldSize + overPos]->clear();
    t=t_;   //更新 目錄深度 t
}

int DHash::func(int x, int t_){
    unsigned int temp=0;
    if(t_ > t) t = t_;
    for(int i=0;i<t;++i)
        temp = temp | (x & (1<<i)?1:0)<<i;
    return temp;
}

void DHash::insert(int data){

    int pos = func(data,t);
    // 若 bucket 不存在
    if(Dr[pos]==0){
        Dr[pos] = new Bucket;
        Dr[pos]->clear();
    } 

    if(Dr[pos]->isFull()){
        // Overflow處理：擴增、rehash
        // Step 0：將要rehash 的資料暫存成陣列，並清空 溢位Bucket 以便「重新放入資料」
        int rhd[3]={Dr[pos]->slot[0],Dr[pos]->slot[1],data};
        Dr[pos]->clear();

        // Step 1：擴增目錄 指向舊Bucket，並將涉及Overflow的目錄 指向新增的bucket
        reSizeDr(t+1,pos);

        // Step 2：rehash 3 data: slot[0],slot[1],data
        for(int i=0;i<3;++i){
            pos = func(rhd[i],t);
            Dr[pos]->push(rhd[i]);
        }   
    }
    else Dr[pos]->push(data);
}

void DHash::printDhash(){
    int size = twoExp(t);
    cout << "Dr  t=" << t << "  size=" << size << endl;
    for(int i=0;i<size;++i){
        cout << "Dr[" << i << "]:\t" << Dr[i] << endl;
    }
    cout << endl;
}

#endif
