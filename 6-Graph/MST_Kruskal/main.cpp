#include <iostream>
#include "graph.hpp"
using namespace std;

int main(){
    ALGraph GL(10,false);
    Set S1(5);
    List L;


    for(char i=1;i<=6;++i)
        GL.InsertVertex(i);

    GL.InsertEdge(1,2,16);  GL.InsertEdge(1,5,19);  GL.InsertEdge(1,6,21);
    GL.InsertEdge(2,3,5);   GL.InsertEdge(2,4,6);   GL.InsertEdge(2,6,11);
    GL.InsertEdge(3,4,10);  
    GL.InsertEdge(4,5,18);  GL.InsertEdge(4,6,14);
    GL.InsertEdge(5,6,33);

    GL.printList();

    GL.MST_Kruskal();

}

