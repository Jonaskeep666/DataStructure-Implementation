#include <iostream>
#include "stack.h"
#include "stack.cpp"
using namespace std;

int isp(char c){
    switch (c){
        case '$': return 1;
        case '*': return 2;
        case '/': return 2;
        case '+': return 4;
        case '-': return 4;
        case '(': return 6;
    }
    return 8;
}
int icp(char c){
    switch (c){
        case '$': return 1;
        case '*': return 2;
        case '/': return 2;
        case '+': return 4;
        case '-': return 4;
        case '(': return 0;
    }
    return -1;
}

/*
演算法概述
1>  遇到'運算元'：直接印出
2>  遇到'運算子'：比較優先權，優先的要在上面or外面
    (1) '新算子' 優先於 'Stack.top 算子'
        -> Push'新算子'到Stack(在上面)
    (2) 'Stack.top 算子' 優先於 '新算子'
        -> 將所有 優先於'新算子' 的 'Stack.top 算子' 都 Pop並印出(在外面)
        -> 再Push'新算子'到Stack
    (3) 定義'運算子'優先權：[(]、[+ -]、[* /]、[$]
        -> 排名越前面，優先權越高，按照優先權高到低：[$]->[* /]->[+ -]
        -> In stack precedence(isp): [$]->[* /]->[+ -]->[(]
        -> In-coming precedence(icp):[(]->[$]->[* /]->[+ -]
        Note: [(]最特別，在Stack裡面 排最後一名，在Stack外面 排第一名
3>  遇到'左括號[(]'：Push到Stack
4>  遇到'右括號[)]'：Pop '左括號[(]' & 上方所有'運算子'，並印出'運算子'
5>  最後 印出 所有 留在Stack中的'運算子'
Note:適用於完整括號的Infix運算式
*/
void infixToPostfix(string s){
    int i=0;
    char bchar='0';
    Stack<char> buffer(20);

    while(s[i]!='#'){
        // 遇到'運算元'，直接印出
        if(s[i]>=65 && s[i]<=90) cout<<s[i];
        // 遇到'右括號'，Pop 所有'運算子'直到'左括號'出來，並印出'運算子'
        else if(s[i]==')') {
            do {
                buffer.Pop(bchar);
                if(bchar != '(') cout << bchar;
            } while (bchar != '(');
        }
        // 遇到'運算子'，比較優先權
        else if(s[i]>=36 && s[i]<=47 && s[i]!=')') {
            // buffer為空，直接Push'運算子'
            if(buffer.isEmpty()) buffer.Push(s[i]);
            // 'Top算子'比'新算子'優先，Pop'Top算子'直到
            // (1) '新算子'比'Top算子'優先 (2) 或 buffer 為空
            // 最後才Push'新算子'
            else if( icp(s[i]) >= isp(buffer.Top()) ){
                do{
                    buffer.Pop(bchar);
                    cout << bchar;
                    if(buffer.isEmpty()) break;
                } while(icp(s[i]) >= isp(buffer.Top()));
                buffer.Push(s[i]);
            }
            // '新算子'比'Top算子'優先，直接Push'運算子'
            else if( icp(s[i]) < isp(buffer.Top()) )
                buffer.Push(s[i]);
        }
        i++;
    }
    //最後將殘留於buffer的'運算子'Pop印出
    while(!buffer.isEmpty()){
        buffer.Pop(bchar);
        cout << bchar;
    }
    puts("");
}

int main(void){
    string infix="((A-(B+C))*D)$(E+F)#";
    string infix2="A*(B+C)*D#";
    string infix3="A*B+C#";

    infixToPostfix(infix3);
}
