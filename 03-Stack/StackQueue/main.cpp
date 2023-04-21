#include <iostream>
#include "bag.h"
#include "bag.cpp"

using namespace std;


int main(void){
    int x;
    Bag b(3); // uses Bag constructor to create array of capacity 3 
    Stack_Bag s(3);// uses Stack constructor to create array of capacity 3 
    
    b.Push(1); 
    b.Push(2); 
    b.Push(3); // use Bag::Push 
    
    s.Push(1); 
    s.Push(2); 
    s.Push(3); // Stack::Push not defined, so use Bag::Push.

    b.Pop(x); // uses Bag::Pop, which calls Bag::IsEmpty 
    s.Pop(x); 
    /* uses Stack::Pop, which calls Bag::IsEmtpy 
    because IsEmpty has not been redefined in Stack. */
}
