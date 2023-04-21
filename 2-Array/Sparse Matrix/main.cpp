#include <iostream>
using namespace std;

#define MaxTerms 10

class SparseMatrix; // forward declaration

class MatrixTerm {
    friend class SparseMatrix;
    private:
        int row, col, value; 
};

class SparseMatrix{
    public:
        //...
        SparseMatrix efficTranspose();
        SparseMatrix fastTranspose();
    private:
        int Rows, Cols, Terms;
        MatrixTerm smArray[MaxTerms];
        //用smArray[]表示一個Sparse Matrix
};

SparseMatrix SparseMatrix::efficTranspose(){
    SparseMatrix b;
    b.Rows = Cols;
    b.Cols = Rows;
    b.Terms = Terms;
    if(Terms > 0) {
        int bI = 0;
        for(int c=0;c<Cols;++c)
            for(int j=0;j<Terms;++j)
                if(smArray[j].col==c){
                    b.smArray[bI].row = c;
                    b.smArray[bI].col = smArray[j].row;
                    b.smArray[bI].value = smArray[j].value;
                    bI++;
                }
    }
    return b;
}

SparseMatrix SparseMatrix::fastTranspose(){
    SparseMatrix b;
    b.Rows = Cols;
    b.Cols = Rows;
    b.Terms = Terms;

    int colAmt[Cols];
    int rowStart[Cols];
    for(int i=0;i<Terms;++i) colAmt[i]=0;
    rowStart[0]=0;

    if(Terms > 0) {
        // smArray[i].col = k -> colAmt[k]++
        for(int i=0;i<Terms;++i) colAmt[smArray[i].col]++;
        //rowStart[i] = sum(colAmt[0]~colAmt[i-1])=sum(colAmt[0]~colAmt[i-2])+colAmt[i-1]
        for(int i=1;i<Cols;++i) rowStart[i] = rowStart[i-1]+colAmt[i-1];

        for(int i=0;i<Terms;++i){
            int j=rowStart[smArray[i].col];
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++;
        }
    }
    return b;
}

int main(void){

}