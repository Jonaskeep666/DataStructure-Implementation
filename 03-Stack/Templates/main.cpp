#include <iostream>
#include "test.h"
using namespace std;

int main(void){
    sign<int> flag(9);
    cout << flag.check() << endl;
}


