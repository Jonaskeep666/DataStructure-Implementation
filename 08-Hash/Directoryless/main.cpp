#include <iostream>
#include <cstdlib>
#include "dlhash.hpp"
using namespace std;



int main(){
    int a[]={32,33,40,41,50,51,53,49};
    int b[]={32,33,44,45,50,51};
    DLHash dlhash(2);

    // printBits(dlhash.func(49,6),6);
    // cout<< endl;
    // printBits(49,6);

    dlhash.printDLHash();

    for(int i=0;i<6;++i)
        dlhash.insert(b[i]);

    dlhash.printDLHash();
            
    dlhash.insert(53);

    dlhash.printDLHash();

    dlhash.insert(49);

    dlhash.printDLHash();
}
