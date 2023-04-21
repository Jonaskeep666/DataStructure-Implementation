#include <iostream>
#include "stack.h"
#include "stack.cpp"
using namespace std;

/*
演算法概述
1>  遇到'左括號'：Push
2>  遇到'右括號'：Pop 並比對 是否與'右括號'有相同樣式
3>  Stack最終必須為'空'
*/

bool parenthesesCheck(string s){
    int i=0;
    char schar='0';
    Stack<char> stack(10);

    while(s[i]!='#'){
        if( s[i]=='(' || s[i]=='[' || s[i]=='{')
            stack.Push(s[i]);
        
        else if( s[i]==')' ){
            if(stack.isEmpty()) return false;
            stack.Pop(schar);
            if(schar!='(') return false;
        }
        else if( s[i]==']' ){
            if(stack.isEmpty()) return false;
            stack.Pop(schar);
            if(schar!='[') return false;
        }
        else if( s[i]=='}' ){
            if(stack.isEmpty()) return false;
            stack.Pop(schar);
            if(schar!='{') return false;
        }
        i++;
    }
    if(stack.isEmpty()) return true;
}

int main(void){
    string s1="7-((X*((X+Y)/(J-3))+Y)/(4-5))#";
    string s2="{x+(y-[a+b])*c-[(d+e)]}/(h-j)#";
    string s3=")A+B(#";
    string s4="((A+B)#";
    cout << parenthesesCheck(s4) << endl;
}
