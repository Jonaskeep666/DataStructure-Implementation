#include <iostream>
#include "stack.h"

using namespace std;

/*
class Stack{
    public:
        Stack(int);
        bool isEmpty() const;
        T& Top() const;
        void Push(const T&);
        void Pop(T&);
    private:
        T *stack;
        int top;
        int capacity;
};
*/

template <class T>
Stack<T>::Stack(int max):capacity(max){
    // capacity = max; = ^^^^^^^^^^^^^
    stack = new T[capacity];
    top = -1;
}

template <class T>
inline bool Stack<T>::isEmpty() const{
    return top == -1;
}
template <class T>
inline T& Stack<T>::Top() const{
    if(isEmpty()) throw "Stack is empty";
    return stack[top];
}

template <class T>
void Stack<T>::Push(const T& newItem){
    if(top == (capacity-1)) throw "Stack is full";
    stack[++top] = newItem;
}
template <class T>
void Stack<T>::Pop(T& popItem){
    if(isEmpty()) throw "Stack is empty";
    popItem = stack[top--];
}
