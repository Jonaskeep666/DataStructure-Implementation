#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <iostream>
using namespace std;

template <class T>
class Queue{
    public:
        Queue(int);
        bool isEmpty() const;
        T Front() const;
        T Rear() const;
        void Push(const T&);
        void Pop(T&);
    private:
        T* queue;
        int front;
        int rear;
        int capacity;
};

template <class T>
Queue<T>::Queue(int max){
    capacity = max;
    queue = new T[capacity];
    front = capacity - 1;
    rear = capacity - 1;
}

template <class T>
inline bool Queue<T>::isEmpty() const{
    return front == rear;
}

template <class T>
inline T Queue<T>::Front() const{
    if(isEmpty()) throw "Queue is empty";
    return queue[(front + 1)%capacity];
}
template <class T>
inline T Queue<T>::Rear() const{
    if(isEmpty()) throw "Queue is empty";
    return queue[rear];
}

template <class T>
void Queue<T>::Push(const T& newItem){
    if((rear+1) == front) cout << "Queue is full" <<endl;
    rear = (rear + 1)%capacity;
    queue[rear] = newItem;
}
template <class T>
void Queue<T>::Pop(T& popItem){
    if(isEmpty()) cout << "Queue is empty" <<endl;
    front = (front + 1)%capacity;
    popItem = queue[front];
}

#endif
