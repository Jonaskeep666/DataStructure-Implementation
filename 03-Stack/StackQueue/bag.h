#ifndef _BAG_H_
#define _BAG_H_

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

#endif
