#ifndef _MYFILE_HPP_
#define _MYFILE_HPP_

#include <iostream>
#include <cstdlib>
using namespace std;

void wirteIntArr(FILE *fptr, int *a,int start, int n){
    rewind(fptr);
    fprintf(fptr,"%d\n",n);
    for(int i=start;i<=n;i++){
        fprintf(fptr,"%d\n",a[i]);
    }
}

void readIntArr(FILE *fptr, int *a,int start, int *n){
    rewind(fptr);
    fscanf(fptr,"%d",n);
    for(int i=start;i<=(*n);i++){
        fscanf(fptr,"%d\n",&a[i]);
    }
}

#endif
