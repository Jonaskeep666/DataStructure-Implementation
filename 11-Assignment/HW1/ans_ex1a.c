#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

//a[i][j]往左上走->a[i-1][j-1]
void goLeftUp(int *i,int *j){
	if(*i-1<0) *i=*i+(SIZE-1);
	else *i=*i-1;
	if(*j-1<0) *j=*j+(SIZE-1);
	else *j=*j-1;
}
int testLeftUp(int i,int j, int a[][SIZE]){
    if(i-1<0) i=i+(SIZE-1);
	else i=i-1;
	if(j-1<0) j=j+(SIZE-1);
	else j=j-1;
    return ((a[i][j]!=0) ? 1:0);
}

//a[i][j]往下走->a[i+1][j]
void goDown(int *i){
	if(*i+1>(SIZE-1)) *i=*i-(SIZE-1);
	else *i=*i+1;
}

//print array
void printArray(int a[][SIZE]){
    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j)
            printf("%d\t",a[i][j]);
        puts("");
    }
}

int main(void){
	int a[SIZE][SIZE]={0};
	
	int i=0, j=(SIZE-1)/2;
	a[i][j]=1;

	for(int k=2;k<(SIZE*SIZE+1);++k){
        if(testLeftUp(i,j,a)) goDown(&i);
        else goLeftUp(&i,&j);
        a[i][j]=k;
	}
    printArray(a);
}