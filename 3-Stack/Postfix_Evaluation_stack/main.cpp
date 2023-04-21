#include <iostream>
#include <cstdio>
#include "stack.h"
#include "stack.cpp"
using namespace std;


int exp(int a, int n){
    int an=1;
    for(int i=0;i<n;++i) an *=a;
    return an;
}
int getNumBuffer(Stack<char>& buffer){
    int num,sum=0,i=0;
    char c;
    while(!buffer.isEmpty()){
        num=0;
        buffer.Pop(c);
        num = (unsigned int)c;
        num -= 48;
        num *= exp(10,i);
        i++;
        sum += num;
    }
    return sum;
}
int calOperand(char c,int& o1, int& o2){
    switch(c){
        case '+': return o1 + o2;
        case '-': return o1 - o2;
        case '*': return o1 * o2;
        case '/': return o1 / o2;
        case '$': return exp(o1,o2);
    }
    return 0;
}

/*
演算法概述
1>  遇到運算元：放進Stack
2>  遇到運算子：取出兩個數字，運算後放回Stack
    運算順序 -> 下方運算元放在前面
3>  直到遇到'#'
Note: ASCII 數字 '48'~'57'
*/
int calPostfix(string s){
    int i=0,num,opd1,opd2;
    int notNum=0;           // 是否將 讀入字元 存到buffer
    Stack<char> buffer(10); // 暫存多位數的數字
    Stack<int> record(50);  // 暫存Postfix運算式的運算元

    // 讀到'結束符號#'跳出迴圈
    while(s[i]!='#'){
        if((s[i]>=48) && (s[i]<=57)){   // 若讀到數字'48'~'57'，存入buffer
            buffer.Push(s[i]);
            if(notNum == 1) notNum = 0;
        }
        if(s[i]==' ' && notNum == 0){   // 若讀到'空格'，將buffer的字元取出
            num = getNumBuffer(buffer); // 並轉換成 十進位整數，放入record
            record.Push(num);
            cout << num << " ";
        }
        // 若讀到'運算子'，取出兩個數字，運算後放回record
        if(s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/' || s[i]=='$'){
            notNum = 1;         // 若讀到'運算子'，下個'空格'不必讀入字元到buffer
            record.Pop(opd2);
            record.Pop(opd1);
            num = calOperand(s[i],opd1,opd2);
            record.Push(num);
            cout << s[i] << " ";
        }
        i++;
    }
    if(record.get_top() == 0){  // 將算好的最後一筆資料傳回
        record.Pop(num);
        cout << "#" << num <<"\n";
        return num;
    }
}

/*
演算法概述
1>  遇到'數字'+1，遇到'運算子'-1
2>  初值 = 0
3>  (總和=+1) && 
    (過程中>0 即stack至少有一個數字) ->合法運算式
*/
bool verifyPostfix(string& s){
    int i=0,sum=0;
    int notNum=1;
    while(s[i]!='#'){
        // 遇到'數字' -> 旗標 notNum=0 -> 下次遇到'空格'則+1
        if((s[i]>=48) && (s[i]<=57)) notNum=0;
        // 上次讀到'數字' +1
        else if(s[i] == ' ' && notNum == 0) sum++;
        // 遇到'算子' -1 -> 旗標 notNum=1 -> 下次遇到'空格'跳過
        else if(s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/' || s[i]=='$'){
            sum--;
            notNum=1;
        }
        // 若過程中 sum<1 則 運算式不合法
        if(notNum==0 && sum <= 0) return false;
        i++;
    }
    if(sum == 1) return true;
}



int main(void){
    string eps="6 2 3 + - 3 8 2 / + * 2 $ 3 + #";
    string c="+ 633 33 + 66 - 60 / 2 $ 54 + #";
    cout << verifyPostfix(c) << endl;
    if(verifyPostfix(c)) calPostfix(c);
}
