#include <iostream>

#include "template_sll.hpp"
using namespace std;

enum Triple {var,ptr,num}; //定義一種型態 enum Triple

class polyNode{
    public:
        polyNode(Triple t){ if(t==var) exp=0; }
    private:
        Triple tri;
        int exp;
        polyNode* next;
        union Data{
            char var;
            polyNode* down;
            int coef;
        }data;
};

class Polynomial{
    public:
        //..
    private:
        polyNode* first;
};

int main(void){
    
}
