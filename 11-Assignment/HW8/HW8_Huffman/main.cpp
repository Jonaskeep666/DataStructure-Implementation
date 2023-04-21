#include <iostream>
#include <cstdlib>
#include <ctime>
#include "huffman.hpp"
using namespace std;


int main(int argc, char *argv[]){
    Filename path;
    CharList clist;
    MinHeap mhp;
    Hufftree tree;
    Buffer dcInput;
    Buffer ecInput;

    bool mode = true;

    if(!setMode(mode,argc,argv,path)) return -1;

    tmr(true);  // Timer ON
    if(mode){
        // path.setOrg("IMG_8813.JPG");
        readDecodeFile(dcInput,path);
        encodeFile(dcInput,clist,mhp,tree);
        writeEncodeFile(clist,dcInput,path);
        printInfo(dcInput,clist);
    }
    else{
        // path.setBin("IMG_8813.JPG.bin");
        readEncodeFile(clist,ecInput,path);
        decodeFile(ecInput,clist,mhp,tree);
        writeDecodeFile(ecInput,path);
        printInfo(ecInput,clist);
    }
    tmr(false); // Timer OFF

    cout << "All done! " << endl;
    return 0;

}
