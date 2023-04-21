#include <iostream>
#include "stack.h"
using namespace std;

template <class T>
Stack<T>::Stack(int max):capacity(max){
    // capacity = max; = ^^^^^^^^^^^^^
    stack = new T[capacity];
    top = -1;
}

template <class T>
int Stack<T>::get_top() const{ return top; }
template <class T>
int Stack<T>::get_capacity() const{ return capacity;}

template <class T>
inline bool Stack<T>::isEmpty() const{ return top == -1; }

template <class T>
void Stack<T>::clearStack(){ top = -1; }

template <class T>
inline T& Stack<T>::Top() const{
    if(isEmpty()) throw "Stack is empty";
    return stack[top];
}

template <class T>
void Stack<T>::Push(T& newItem){
    if(top == (capacity-1)) throw "Stack is full";
    stack[++top] = newItem;
}
template <class T>
void Stack<T>::Pop(T& popItem){
    if(isEmpty()) throw "Stack is empty";
    popItem = stack[top--];
}

