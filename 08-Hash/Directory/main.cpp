#include <iostream>
#include <cstdlib>
#include "dhash.hpp"
using namespace std;



int main(){
    int a[]={32,33,40,41,50,51,53,49};
    DHash dhash(2);

    // printBits(dhash.func(49,6),6);
    // cout<< endl;
    // printBits(49,6);

    dhash.printDhash();

    for(int i=0;i<6;++i)
        dhash.insert(a[i]);

    dhash.printDhash();
            
    dhash.insert(53);

    dhash.printDhash();

    dhash.insert(49);

    dhash.printDhash();
}
