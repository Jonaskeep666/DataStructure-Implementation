#include <iostream>
#include "graph.hpp"
using namespace std;

int main(){
    ALGraph GL(10,true);
    VertexHeap vh(7);
    List L;


    for(char i=1;i<=8;++i)
        GL.InsertVertex(i);

    // GL.InsertEdge(1,2,16);  GL.InsertEdge(1,5,19);  GL.InsertEdge(1,6,21);
    // GL.InsertEdge(2,3,5);   GL.InsertEdge(2,4,6);   GL.InsertEdge(2,6,11);
    // GL.InsertEdge(3,4,10);  
    // GL.InsertEdge(4,5,18);  GL.InsertEdge(4,6,14);
    // GL.InsertEdge(5,6,33);

     
    GL.InsertEdge(2,1,300);
    GL.InsertEdge(3,2,800);   GL.InsertEdge(3,1,1000);  
    GL.InsertEdge(4,3,1200); 
    GL.InsertEdge(5,4,1500);  GL.InsertEdge(5,6,250); 
    GL.InsertEdge(6,4,1000);  GL.InsertEdge(6,7,900); GL.InsertEdge(6,8,1400);
    GL.InsertEdge(7,8,1000);
    GL.InsertEdge(8,1,1700);

    GL.printList();

    GL.SP_Dijkstra(5);
        
    

}

