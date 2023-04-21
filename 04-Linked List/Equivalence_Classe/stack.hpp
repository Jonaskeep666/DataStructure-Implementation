#ifndef _STACK_HPP_
#define _STACK_HPP_

#include <iostream>
using namespace std;

template <class T>
class Stack{
    public:
        Stack(int);
        bool isEmpty() const;
        T Top() const;
        void Push(const T&);
        void Pop(T&);
    private:
        T *stack;
        int top;
        int capacity;
};

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
inline T Stack<T>::Top() const{
    if(isEmpty()){
        cout << "Stack is empty";
        return;
    } 
    return stack[top];
}

template <class T>
void Stack<T>::Push(const T& newItem){
    if(top == (capacity-1)) {
        cout << "Stack is full";
        return;
    }
    stack[++top] = newItem;
}

template <class T>
void Stack<T>::Pop(T& popItem){
    if(isEmpty()){
        cout << "Stack is empty";
        return;
    } 
    popItem = stack[top--];
}

#endif