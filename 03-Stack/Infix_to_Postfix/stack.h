#ifndef _STACK_H_
#define _STACK_H_

using namespace std;

template <class T>
class Stack{
    public:
        Stack(int);
        int get_top() const;
        int get_capacity() const;
        bool isEmpty() const;
        void clearStack();
        T& Top() const;
        void Push(T&);
        void Pop(T&);
    private:
        T *stack;
        int top;
        int capacity;
};

#endif
