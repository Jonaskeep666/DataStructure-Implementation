#ifndef _QUEUE_H_
#define _QUEUE_H_

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

#endif
