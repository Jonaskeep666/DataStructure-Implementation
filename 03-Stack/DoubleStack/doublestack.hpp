#ifndef _DOUBLESTACK_H_
#define _DOUBLESTACK_H_

template <class T>
class DoubleStack{
    public:
        DoubleStack(int);
        void clearStack() const;
        bool isEmpty() const;
        T Top(int) const;
        void Push(const T&,int);
        void Pop(T&,int);
    private:
        T *stack;
        int top1;
        int top2;
        int capacity;
};

template <class T>
DoubleStack<T>::DoubleStack(int Max){
    capacity=Max;
    stack = new T[capacity];
    top1=-1;
    top2=capacity;
};

template <class T>
void DoubleStack<T>::clearStack() const{
    top1=-1;
    top2=capacity;
}

template <class T>
inline bool DoubleStack<T>::isEmpty() const {
    return (top1 == -1 && top2 == capacity);
}

template <class T>
T DoubleStack<T>::Top(int stackNum) const{
    return (stackNum == 1) ? top1 : top2;
}
template <class T>
void DoubleStack<T>::Push(const T& e, int stackNum){
    if(top1+1 == top2) throw "Doublestack is full."
    else if(stackNum == 1) stack[++top1]=e;
    else if(stackNum == 2) stack[--top2]=e;
}
template <class T>
void DoubleStack<T>::Pop(T& e, int n){
    if(stackNum == 1){
        if(top1 == -1) throw "Stack1 is empty."
        e=stack[top1--];
    }
    else if(stackNum == 2){
        if(top2 == n) throw "Stack1 is empty."
        e=stack[top2++];
    }
}

#endif