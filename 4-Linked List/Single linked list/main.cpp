#include <iostream>
#include "template_sll.hpp"
using namespace std;

struct Term{
    int exp;
    int coef;
};
ostream& operator<<(ostream& os, Term& term){
    os << "(" << term.coef << ")";
    os << "x^" << term.exp;
    return os;
}

int main(void){
    Term t1={1,3}, t2={2,4}, t3={3,5}, t4={4,6};
    Term t = {9,9};
    List<Term> p1,p2;

    // test ~List - OK
    // test isEmpty() - OK
    // test getSize() - OK

    // test Traversal
    // test getAddr(int index) - OK

    // test Access
    // test T getAt(int index) - OK (要用一個變數去接回傳值)
    // test Node<T>* getFirst(){return first;} - OK
    // test Node<T>* getLast(); - OK
    // test Node<T>* getNext(int index); - OK

    // test insertAfter(int index, T term) - OK
    // test insertFront(T term) - OK
    // test insertBack(T term) - OK

    // test Maintenance
    // test setAt(int index, T term); - OK
    // test deleteNode(int index); - OK                 
    // test deleteBack() - OK

    p1.insertBack(t1); cout<<p1; //cout<< p1.getSize()<<endl;
    p1.insertBack(t2); cout<<p1; //cout<< p1.getSize()<<endl;
    p1.insertBack(t3); cout<<p1; //cout<< p1.getSize()<<endl;
    p1.insertBack(t4); cout<<p1; //cout<< p1.getSize()<<endl;

    p2.insertBack(t4); cout<<p2; //cout<< p1.getSize()<<endl;
    p2.insertBack(t3); cout<<p2; //cout<< p1.getSize()<<endl;
    p2.insertBack(t2); cout<<p2; //cout<< p1.getSize()<<endl;
    p2.insertBack(t1); cout<<p2; //cout<< p1.getSize()<<endl;

    p2.invertList(); cout<<p2;
    p1.ConcatenateList(p2); cout<<p1;


}
