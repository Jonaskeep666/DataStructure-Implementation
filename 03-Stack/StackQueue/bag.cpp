#include <iostream>
#include "bag.h"
using namespace std;

/*
class Bag {
    public:
        Bag(int);
        virtual int Size() const;
        virtual bool isEmpty() const;
        virtual void Push(const int&);
        virtual void Pop(int&);
    protected:
        int *array;
        int top;
        int capacity;
};

class Stack_Bag : public Bag {
    public:
        Stack_Bag(int);
        ~Stack_Bag();
        int Top() const;
        void Pop(int&);
};
*/

Bag::Bag(int max):capacity(max){
    array = new int[capacity];
    top = -1;
}
int Bag::Size() const{
    return capacity;
}
bool Bag::isEmpty() const{
    return top == -1;
}
void Bag::Push(const int& newItem){
    if(top == (capacity-1)) throw "It's full";
    array[++top]=newItem;
}
void Bag::Pop(int& popItem){
    if(isEmpty()) throw "It's empty";
    popItem = array[top--];
}

Stack_Bag::Stack_Bag(int max):Bag(max) {}
Stack_Bag::~Stack_Bag(){}

int Stack_Bag::Top() const{
    if(isEmpty()) throw "Stack_Bag is empty";
    return top;
}
void Stack_Bag::Pop(int& popItem){
    if(isEmpty()) throw "Stack_Bag is empty";
    popItem = array[top--];
}
