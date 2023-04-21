#ifndef _STACK_H_
#define _STACK_H_

using namespace std;

template <class T>
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

#endif
