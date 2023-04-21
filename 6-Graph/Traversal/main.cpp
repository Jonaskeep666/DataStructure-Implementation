#include <iostream>
#include "graph.hpp"
using namespace std;

int main(){
    AMGraph GM(10,false);
    ALGraph GL(10,false);
    List L;


    for(char i=49;i<=56;++i)
        GL.InsertVertex(i);

    GL.InsertEdge('1','2');
    GL.InsertEdge('1','3');

    GL.InsertEdge('2','4');
    GL.InsertEdge('2','5');
    GL.InsertEdge('3','6');
    GL.InsertEdge('3','7');

    GL.InsertEdge('4','8');
    GL.InsertEdge('5','8');
    GL.InsertEdge('6','8');
    GL.InsertEdge('7','8'); 

    GL.printList();

    GL.DFS('1');
    cout << endl;
    GL.DFS('5');
    cout << endl;

    GL.BFS('1');
    cout << endl;
    GL.BFS('5');
    cout << endl;

    // for(char i=49;i<=56;++i)
    //     GM.InsertVertex(i);

    // GM.InsertEdge('1','2');
    // GM.InsertEdge('1','3');

    // GM.InsertEdge('2','4');
    // GM.InsertEdge('2','5');
    // GM.InsertEdge('3','6');
    // GM.InsertEdge('3','7');

    // GM.InsertEdge('4','8');
    // GM.InsertEdge('5','8');
    // GM.InsertEdge('6','8');
    // GM.InsertEdge('7','8'); 

    // GM.printMatrix();

    // GM.DFS('1');
    // cout << endl;
    // GM.DFS('5');
    // cout << endl;

    // GM.BFS('1');
    // cout << endl;
    // GM.BFS('5');
    // cout << endl;





    // L.insertBack('C');
    // L.insertBack('B');
    // L.insertBack('A');

    // L.deleteNode('B');
    // L.insertBack('B');

    // L.printList();
    // L.deleteList();
    // L.printList();


    // GL.InsertVertex('A');
    // GL.InsertVertex('B');
    // GL.InsertVertex('C');
    // GL.InsertVertex('D');

    // GL.InsertEdge('A','B');
    // GL.InsertEdge('A','C');

    // GL.InsertEdge('B','A');
    // GL.InsertEdge('B','C');
    // GL.InsertEdge('B','D');

    // GL.InsertEdge('C','A');
    // GL.InsertEdge('C','B');
    // GL.InsertEdge('C','D');

    // GL.InsertEdge('D','B');
    // GL.InsertEdge('D','C');

    // GL.DeleteVertex('B');

    // GL.printList();

    // GM.InsertVertex('A');
    // GM.InsertVertex('B');
    // GM.InsertVertex('C');
    // GM.InsertVertex('D');

    // GM.InsertEdge('A','B');
    // GM.InsertEdge('A','C');

    // GM.InsertEdge('B','A');
    // GM.InsertEdge('B','C');
    // GM.InsertEdge('B','D');

    // GM.InsertEdge('C','A');
    // GM.InsertEdge('C','B');
    // GM.InsertEdge('C','D');

    // GM.InsertEdge('D','B');
    // GM.InsertEdge('D','C');

    // GM.DeleteVertex('B');

    // GM.printMatrix();

}

