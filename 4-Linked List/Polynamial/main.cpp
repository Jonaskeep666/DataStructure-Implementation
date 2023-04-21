#include <iostream>
#include <cstdlib>
#include <ctime>
#include "template_sll.hpp"
using namespace std;

struct Term{
    int exp;
    int coef;
    Term set(int e, int c) {exp = e; coef = c; return *this;}
};
ostream& operator<<(ostream& os,Term& term){
    os << "(" << term.coef << ")x^" << term.exp;  
    return os;
}


class Polynomial{
    public:
        List<Term> getList(){return poly;}
        void addTerm(Term term);
        Polynomial& operator+(Polynomial& b);
        Polynomial& operator*(Polynomial& b);
        void printPoly();
    private:
        List<Term> poly;
};

// 新增 多項式「項次」
void Polynomial::addTerm(Term term){
    int i=1;
    if(term.coef) {
        if(poly.isEmpty()) 
            poly.insertFront(term);
        else if(!poly.getAt(1).coef) 
            poly.setAt(1,term);
        else if(term.exp > poly.getAt(1).exp) 
            poly.insertFront(term);
        else if(term.exp == poly.getAt(1).exp){
            term.coef += poly.getAt(1).coef;
            if(term.coef) poly.setAt(1,term);
            else poly.deleteNode(1);
        }
        else{
            while(poly.getNext(i)){
                if(poly.getAt(i).exp > term.exp && term.exp >= poly.getAt(i+1).exp){
                    if(term.exp == poly.getAt(i+1).exp){
                        term.coef += poly.getAt(i+1).coef;
                        if(term.coef) poly.setAt(i+1,term);
                        else poly.deleteNode(i+1);
                    }
                    else poly.insertAfter(i,term);
                    return;
                }
                i++;
            }
            if(poly.getAt(i).exp > term.exp && !poly.getNext(i))
                poly.insertBack(term);
        }
    }
    else if(poly.isEmpty()) poly.insertBack(term.set(0,0));
}

// 多項式加法 - 課本法
Polynomial& Polynomial::operator+(Polynomial& b){
    Polynomial *c = new Polynomial;
    Term temp;
    int ai=1, bi=1;
    while(poly.getAddr(ai) && b.poly.getAddr(bi)){
        if(poly.getAt(ai).exp == b.poly.getAt(bi).exp){
            temp = poly.getAt(ai);
            temp.coef = poly.getAt(ai).coef + b.poly.getAt(bi).coef;
            if(temp.coef) c->poly.insertBack(temp);
            ai++;
            bi++;
        }
        else if(poly.getAt(ai).exp < b.poly.getAt(bi).exp){
            c->poly.insertBack(b.poly.getAt(bi));
            bi++;
        }
        else{
            c->poly.insertBack(poly.getAt(ai));
            ai++;
        }
    }
    while(poly.getAddr(ai)){
        if(poly.getAt(ai).coef) c->poly.insertBack(poly.getAt(ai));
        ai++;
    }
    while(b.poly.getAddr(bi)){
        if(b.poly.getAt(bi).coef) c->poly.insertBack(b.poly.getAt(bi));
        bi++;
    }
    if(c->poly.isEmpty()) c->poly.insertBack(temp.set(0,0));
    return *c;
}


//多項式加法 - 配合 addTerm()
// Polynomial& Polynomial::operator+(Polynomial& b){
//     Polynomial *c = new Polynomial;
//     Term temp;

//     for(int i=1;poly.getAddr(i);++i)
//         c->addTerm(poly.getAt(i));
//     for(int i=1;b.poly.getAddr(i);++i)
//         c->addTerm(b.poly.getAt(i));
//     if(c->poly.isEmpty()) c->poly.insertBack(temp.set(0,0));
//     return *c;
// }

// 多項式乘法
Polynomial& Polynomial::operator*(Polynomial& b){
    Polynomial *c = new Polynomial;
    Term temp;
    int ai=1, bi=1;
    while(poly.getAddr(ai)){
        while(b.poly.getAddr(bi)){
            temp.coef = poly.getAt(ai).coef * b.poly.getAt(bi).coef;
            temp.exp = poly.getAt(ai).exp + b.poly.getAt(bi).exp;
            if(temp.coef) c->addTerm(temp);
            bi++;
        }
        ai++;
        bi=1;
    }
    if(c->poly.isEmpty()) c->poly.insertBack(temp.set(0,0));
    return *c;
}

void Polynomial::printPoly(){
    for(int i=1;poly.getAddr(i);++i){
        // 若次方=0，僅印出係數；若次方≠0，則印出 係數+次方
        if(!poly.getAt(i).exp) cout <<"("<< poly.getAt(i).coef << ")";
        else {
            cout <<"("<< poly.getAt(i).coef << ")x^";
            cout << poly.getAt(i).exp;
        }
        // 若不是最後一項，項與項之間 印出"+"
        if(poly.getNext(i)) cout<<"+";
    }
    cout<<endl;
    cout<<poly;
}

int main(void){
    Polynomial A[3],B[3],C[3],D[3];
    Term temp;
    int j=0;

    int p=1,q=1;

    // while(p || q){
    //     cin >> p;
    //     if(p){
    //         for(int i=0;i<p;++i){
    //             cin >> temp.coef >> temp.exp;
    //             A[j].addTerm(temp);
    //         }
    //     }
    //     else A[j].addTerm(temp.set(0,0));
    //     cin >> q;
    //     if(q){
    //         for(int i=0;i<q;++i){
    //             cin >> temp.coef >> temp.exp;
    //             B[j].addTerm(temp);
    //         }
    //     }
    //     else B[j].addTerm(temp.set(0,0));
    //     j++;
    // }

    // for(j=0;j<3;++j){
    //     cout << endl;
    //     cout << "A = "; A[j].printPoly();
    //     cout << "B = "; B[j].printPoly();

    //     C[j] = A[j] + B[j];
    //     cout << "C = A + B"<<endl; 
    //     cout << "= "; C[j].printPoly();

    //     D[j] = A[j] * B[j];
    //     cout << "D = A * B"<<endl; 
    //     cout << "= "; D[j].printPoly();
    // }


    // srand(time(NULL));

    // int r;
    // int count[6]={0};

    // while(count[5]<5){
    //     r = (rand()%5);
    //     count[5]++;
    //     cout << r <<":" <<endl;;
    //     cout << t[r] <<endl;;
    //     B.addTerm(t[r]); B.printPoly(); 
    // }

    // for(int j=0;j<6;count[j++]=0);
    
    // while(count[5]<5){
    //     r = (rand()%5);
    //     count[5]++;
    //     cout << r <<":" <<endl;;
    //     cout << t[r] <<endl;;
    //     A.addTerm(t[r]); A.printPoly(); 
    // }

    // test 1
    // A.addTerm(temp.set(2,1));
    // A.addTerm(temp.set(1,1));
    // A.addTerm(temp.set(0,1));

    // B.addTerm(temp.set(0,0));

    // test 2
    // A.addTerm(temp.set(5,3));
    // A.addTerm(temp.set(1,1));
    // A.addTerm(temp.set(1,1));

    // B.addTerm(temp.set(1,-2));
    // B.addTerm(temp.set(2,1));

    // test 3
    // A[0].addTerm(temp.set(0,0));
    // A[0].addTerm(temp.set(0,0));
    // A[0].addTerm(temp.set(1,5));
    // A[0].addTerm(temp.set(2,-7));

    // B[0].addTerm(temp.set(1,-5));
    // B[0].addTerm(temp.set(0,7));

    // A[0].printPoly();
}
