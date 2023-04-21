#ifndef _TEMPLATE_SLL_HPP_
#define _TEMPLATE_SLL_HPP_

#include <iostream>
using namespace std;

template <class T>
class List;

template <class T>
ostream& operator<<(ostream& os,List<T> &L);

template <class T>
class ListIterator;

template <class T>
class Node{
    friend class List<T>;
    friend class ListIterator<T>;
    friend ostream& operator<<<T>(ostream& os,List<T> &L);

    public:
        Node(){ next = 0;}
        Node(T term, Node* link=0){
            data = term;
            next = link;
        }
    protected:
        T data;
        Node* next;
};

template <class T>
class List{
    friend ostream& operator<<<T>(ostream& os,List<T> &L);
    friend class ListIterator<T>;

    public:
        List(){first=0; size=0; last=0;}
        ~List(); 
        bool isEmpty(){ return first == 0; }
        int getSize(){ return size; } 

        //Traversal
        Node<T>* getAddr(int index);

        //Access
        T getAt(int index);
        Node<T>* getFirst(){return first;}
        Node<T>* getLast();
        Node<T>* getNext(int index);

        void insertAfter(int index, T term);
        void insertFront(T term);
        void insertBack(T term);

        //Maintenance
        void setAt(int index, T term); 
        void deleteNode(int index);                 
        void deleteBack();

        //Revision
        void invertList();
        void ConcatenateList(List<T> &b);
    protected:
        Node<T>* first;
        Node<T>* last;
        int size;
};

template <class T>
class ListIterator{
    public:
        ListIterator(Node<T>* first=0){ current = first;}
        
        T& operator*() const {return current->data;}
        T* operator->() const {return &current->data;}

        ListIterator& operator++(){ current = current->next; return *this;}

        bool operator!=(const ListIterator right)const{return current!=right.current;}
        bool operator==(const ListIterator right)const{return current==right.current;}
    private:
        Node<T>* current;
};

// Overload << for List
template <class T>
ostream& operator<<(ostream& os,List<T> &L){
    Node<T>* current = L.first;
    if(L.isEmpty()) os << "Empty!" <<endl;
    else{
        while(current){
            os << "[" << current->data;
            current = current->next;
            if(!current) os << "]";
            else os << "]->";
        }
        os << endl;
    }
    return os;
}

// Destructor
template <class T>
List<T>::~List(){
    Node<T>* current = first;
    while(current){
        first = current;
        current = current->next;
        delete first;
    }
    first = last = 0;
}

/********* Traversal *********/

// 取得 第index個 Node 的位址
template <class T>
Node<T>* List<T>::getAddr(int index){
    Node<T>* current = first;
    int i=1;
    if(isEmpty()){ cout<<"Empty!"; return 0;}
    else{
        //找 第index個 Node
        while(current && i<index){
            current = current->next;
            i++;
        }
        return current;    
    }
}


/********* Access *********/
// 取得 第index個 Node 的 data
template <class T>
T List<T>::getAt(int index){
    return getAddr(index)->data;
}

// 取得 last 尾指標
template <class T>
Node<T>* List<T>::getLast(){
    Node<T>* current = first;
    if(last) return last;
    else{
        while(current->next){current = current->next;}
        last = current;
        return last;
    }
}

// 取得 第index個 Node 的 next
template <class T>
Node<T>* List<T>::getNext(int index){
    return getAddr(index)->next;
}

// 在 第index個Node 之後插入 新Node
template <class T>
void List<T>::insertAfter(int index, T term){
    Node<T>* current;
    Node<T>* newNode = new Node<T>(term);
    if(isEmpty()) first = last = newNode;
    else{
        current = getAddr(index);
        newNode->next = current->next;
        current->next = newNode;
        if(!newNode->next) last=newNode; //新增到尾Node，要重新指定last
    }
    size++;
}

//在 首端 插入新Node
template <class T>
void List<T>::insertFront(T term){
    Node<T>* newNode = new Node<T>(term);
    if(isEmpty()) first = last = newNode;
    else{
        newNode->next = first;
        first = newNode;
    }
    size++;
}

// 在 尾端 插入新Node
template <class T>
void List<T>::insertBack(T term){
    Node<T>* newNode = new Node<T>(term);
    if(isEmpty()) first = last = newNode;
    else{
        last->next = newNode;
        last = newNode;
    }
    size++;
}

/********* Maintenance *********/
// 設定 第index個Node 的data
template <class T>
void List<T>::setAt(int index, T term){
    getAddr(index)->data = term;
}

// 刪除 第index個Node
template <class T>
void List<T>::deleteNode(int index){
    Node<T>* current = first;
    Node<T>* previous = first;
    if(isEmpty()){ cout<<"Empty!"; return;}
    else if(index == 1) first = current->next;
    else{
        //找前一個Node
        previous = getAddr(index-1);
        current = previous->next;
        previous->next = current->next;
        if(current == last) last = previous; //刪到尾Node，要重新指定last
    }
    delete current;
    size--;
}

// 刪除 尾端Node
template <class T>
void List<T>::deleteBack(){
    Node<T>* current = first;
    if(!last) getLast();
    if(isEmpty()){ cout<<"Empty!"; return;}
    else if( last == first) { 
        delete first;
        first = last = 0;
    }
    else{
        while(current->next != last) {current = current->next;}
        current->next = 0;
        delete last;
        last = current;
    }
    size--;
}

/********* Revision *********/
// 反轉 List
template <class T>
void List<T>::invertList(){
    Node<T>* current = first;
    Node<T>* _next = first;
    Node<T>* previous = NULL;

    while(_next){   //當下一個Node不是Null時
        _next = _next->next;        //n往前走
        current->next = previous;   //改指向(c指向p)
        //c,p往前走
        previous = current; //不可以previous=previous->next 因為previous已經改過指向了
        current = _next;
    }
    first = previous;
}

// 串接 List
template <class T>
void List<T>::ConcatenateList(List<T> &b){
    if(isEmpty()){
        first = b.first;
        last = b.last;
    }
    else if(!b.isEmpty()){
        last->next = b.first;
        last = b.last;
    }
    size += b.size;
    b.first = b.last = 0;
}

#endif
