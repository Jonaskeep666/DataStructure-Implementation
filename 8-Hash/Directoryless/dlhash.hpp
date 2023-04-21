#ifndef _DLHASH_HPP_
#define _DLHASH_HPP_

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

struct OFN{ //Overflow Area List Node
    int d;
    OFN* next;
    void set(int data){ d=data; next=0;}
};

struct OFA{ //Overflow Area List 
    OFN* first;
    void clr(){first=0;}

    bool isEmpty(){return first == 0;}

    void insertBack(int data){
        OFN* newNode = new OFN;
        newNode->set(data);
        if(isEmpty()) first = newNode;
        else{
            OFN* current = first;
            while(current->next){current=current->next;}
            current->next = newNode;
        }
    }
    int popNode(OFN* delNode){
        int popData = delNode->d;
        if(delNode == first) first = delNode->next;
        else{
            OFN* previous = first;
            while(!(previous->next == delNode)){previous=previous->next;}
            previous->next = delNode->next;
        }
        delete delNode;
        return popData;
    }
    void printList(){
        if(isEmpty()) cout << "Empty!";
        else{
            OFN* current = first;
            while(current){
                cout << "[" << current->d << "] ";
                current = current->next;
            }
        }
    }
};

struct Bucket{
    int slot[2];    // 2 Slot
    void clear(){ slot[0]=-1; slot[1]=-1; }

    bool isFull(){ return (slot[0] >=0 && slot[1] >=0); }
    bool isEmpty(){return (slot[0] < 0 && slot[1] < 0); }
    void push(int data){
        if(isFull()){cout << "Bucket full!!" << endl; return;}
        else if(isEmpty()) slot[0]=data;
        else if(slot[1]==-1) slot[1]=data;
    }
};

ostream& operator<<(ostream& os, Bucket bucket){
    if(bucket.slot[0]==-1) os << "[__]-";
    else os << "[" << bucket.slot[0] << "]-";
    if(bucket.slot[1]==-1) os << "[__]";
    else os << "[" << bucket.slot[1] << "]";

    return os;
}

class DLHash{
    public:
        DLHash(int t_){
            t=t_; q=0;
            size = twoExp(t)+q;
            Dr = new Bucket[size];
            for(int i=0;i<size;++i) Dr[i].clear();

            ofaList = new OFA;
            ofaList->clr();
        }
        // Hash function：取(x)的前(tb)個位元 作為「Bucket位置」
        int func(int x,int tb);

        // 擴增Table 1 Bucket (q++)
        // 並將 Dr[q-1] & Dr[size-1] 清空、修改 Dr[q-1] & Dr[size-1] 的 h(x,t)->h(x,t+1)
        void addBucket();

        void insert(int data);

        void printDLHash();
    private:
        Bucket* Dr;    //指向Table的指標
        int size;      //bucket個數
        int t,q;       
        OFA* ofaList;      //Overflow Area
};

void DLHash::addBucket(){
    // 擴增 1 bucket，並修改 Table size
    q++;
    if(q>twoExp(t)){ t++; q=1; } //若 q > 2^t，則重置q=1 & t+1
    size = twoExp(t)+q;

    Bucket* extDr = new Bucket[size];
    for(int i=0;i<(size-1);++i){
        extDr[i] = Dr[i];
    }
    delete[] Dr;
    Dr = extDr;
    Dr[q-1].clear();     //清空 Dr[q-1]
    Dr[size-1].clear();  //清空 Dr[size-1]
}

int DLHash::func(int x, int tb){
    unsigned int temp=0;
    for(int i=0;i<tb;++i)
        temp = temp | (x & (1<<i)?1:0)<<i;
    return temp;
}

void DLHash::insert(int data){
    int pos = func(data,t);

    if(Dr[pos].isFull()){
        // Overflow處理：擴增、rehash
        
        // Step 0：將 insert data 放入 Overflow area、將 rehash bucket的資料暫存
        ofaList->insertBack(data);
        int rhd[2]={Dr[q].slot[0],Dr[q].slot[1]};

        // Step 1：擴增Table (q++)
        // 並將 Dr[q-1] & Dr[size-1] 清空、修改 Dr[q-1] & Dr[size-1] 的 h(x,t)->h(x,t+1)
        addBucket();

        // Step 2：要rehash的bucket：Dr[q-1] & Overflow area
        
        // Step 2-1：rehash Dr[q-1]
        int ptemp = 0;
        for(int i=0;i<2;++i){
            ptemp = func(rhd[i],t+1);  // 以h(x,t+1) rehash 
            Dr[ptemp].push(rhd[i]);
        }

        // Step 2-1：rehash Overflow area：只要 func(data,t)==q-1 的，都抓出來 嘗試rehash
        OFN* current = ofaList->first;
        while(current){
            if(func(current->d,t)==q-1){
                ptemp = func(current->d,t+1);  // 以h(x,t+1) rehash 
                if(Dr[ptemp].isFull()) current = current->next; // 滿了就繼續留在 ofa
                else{
                    Dr[ptemp].push(current->d);
                    OFN* delNode = current;
                    current = current->next;
                    ofaList->popNode(delNode);
                }
            }
            else current = current->next;
        }       
    }
    else Dr[pos].push(data);
}

void DLHash::printDLHash(){
    cout << "Dr  t=" << t << "  size=" << size << endl;
    for(int i=0;i<size;++i){
        cout << "Dr[" << i << "]:\t" << Dr[i] << endl;
    }

    cout << "Overflow:";
    ofaList->printList();
    cout << "\n" << endl;
}

#endif
