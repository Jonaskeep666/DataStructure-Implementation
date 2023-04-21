#include <iostream>
#include "dll.hpp"
using namespace std;

int main(){
    DLList<int> dll;

    cout << dll.isEmpty() <<endl;
    for(int i=8;i>0;--i) dll.insertAfter(0,i);
    cout << dll.isEmpty() <<endl;
    cout << "Size:" << dll.getSize() <<endl;
    cout << dll;
    for(int i=1;i<9;++i) cout << dll.getAt(i) << ",";
    cout << endl;

    dll.deleteNode(1);
    cout << "Size:" << dll.getSize() <<endl;
    cout << dll;
}
