#include <iostream>
using namespace std;

class TSet{
    friend  ostream& operator<<(ostream&, TSet&);
    friend void operator>>(istream&, TSet&);

    public:
        TSet();
        TSet(string);
        TSet(string,string);
        void assignSet(string);
        TSet operator+(TSet&);
        TSet operator-(TSet&);
        TSet operator*(TSet&);

        string operator>=(TSet&);
        string in(char);

    private:
        string name;
        char set[256];
};

TSet::TSet(){
    for(int i=0;i<256;++i) set[i]=0;
}
TSet::TSet(string n){
    for(int i=0;i<256;++i) set[i]=0;
    name = n;
}
TSet::TSet(string n, string s){
    int i=0;
    for(int i=0;i<256;++i) set[i]=0;
    while(s[i]!='\0'){
        set[(unsigned int)s[i]]=s[i];
        i++;
    }
    name = n;
}

TSet TSet::operator+(TSet& b){
    TSet c;
    for(int i=0;i<256;++i) c.set[i]= set[i] | b.set[i];
    c.name = name + "+" + b.name;
    return c;
}
TSet TSet::operator-(TSet& b){
    TSet c;
    for(int i=0;i<256;++i) c.set[i]= set[i] & ~(b.set[i]);
    c.name = name + "-" + b.name;
    return c;
}
TSet TSet::operator*(TSet& b){
    TSet c;
    for(int i=0;i<256;++i) c.set[i]= set[i] & b.set[i];
    c.name = name + "*" + b.name;
    return c;
}

string TSet::operator>=(TSet& b){
    int flag=0;
    for(int i=0;i<256;++i){
        if((set[i] & b.set[i]) == b.set[i]);
        else flag++;
    }
    if(flag==0) return (name+" contains "+b.name);
    else return (name+" does not contain "+b.name);
}
string TSet::in(char c){
    int flag=1;
    string s="c"; s[0]=c;
    for(int i=0;i<256;++i){
        if((set[i] & c) == c) flag=0;
    }
    if(flag==0) return ("'"+s+"'"+" is in "+name);
    else return ("'"+s+"'"+" is not in "+name);
}

ostream& operator<<(ostream& os, TSet& t){
    os << t.name << ": {";
    for(int i=0;i<256;++i) os << t.set[i];
    os << "}";
    return os;
}
void operator>>(istream& is, TSet& t){
    char c='&';
    while(c!='\n'){
        is.get(c);
        if(c!='\n') t.set[(unsigned int)c] = c;
    }
}


int main(void){
    int N=0;

    cin >> N;

    for(int k=0;k<N;++k){ 
        TSet A("A"),B("B");
        char x; 

        cin.ignore();
        cin >> A;
        cin >> B;
        cin.get(x);
        

        TSet C, D, E, F;
        C = A+B;
        D = A*B;
        E = A-B;
        F = B-A;

        cout << endl;
        cout <<"Test Case "<< k+1 <<":"<<endl;
        cout << A << endl;
        cout << B << endl;
        cout << C << endl;
        cout << D << endl;
        cout << E << endl;
        cout << F << endl;
        cout << (A>=B) <<endl;
        cout << (B>=A) <<endl;
        cout << A.in(x) <<endl;
        cout << B.in(x) <<endl;

    }
    return 0;
}




/*
3
abcdef
cfehi
h
3abf4ec
43
g
a%5A wdt
 5At
 
Test Case 1:
A: {abcdef}
B: {cefhi}
A+B: {abcdefhi}
A*B: {cef}
A-B: {abd}
B-A: {hi}
A does not contain B
B does not contain A
'h' is not in A
'h' is in B

Test Case 2:
A: {34abcef}
B: {34}
A+B: {34abcef}
A*B: {34}
A-B: {abcef}
B-A: {}
A contains B
B does not contain A
'g' is not in A
'g' is not in B


Test Case 3:
A: { %5Aadtw}
B: { 5At}
A+B: { %5Aadtw}
A*B: { 5At}
A-B: {%adw}
B-A: {}
A contains B
B does not contain A
' ' is in A
' ' is in B
*/