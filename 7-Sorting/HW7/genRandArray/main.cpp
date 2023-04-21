#include <iostream>
#include <cstdlib>
#include <ctime>
#include "myfile.hpp"
using namespace std;

/*
1> 開檔案 讀寫

FILE *fptr;
fptr = fopen("/Users/jonaswu/cfile/abc.txt","r+"); 
if(fptr == NULL){
    cout << The file doesn't exist. Create a new one.<< endl;
    fptr = fopen("/Users/jonaswu/cfile/abc.txt","w+"); 
}
else{
    // 讀寫檔案
}

2>  設定游標
    rewind(fptr)    //游標回到開頭
    fseek(fptr,m,SEEK_CUR); //游標從目前位置，往後指 m bytes
    fseek(fptr,m,SEEK_SET); //游標從檔案開頭，往後指 m bytes


3>  自檔案讀入資料(fscanf()/fread())
    fread(a,sizeof(int),n,fptr);    //從fptr檔案 讀取n筆 sizeof(int)大小的資料 存入 指標a 指向的空間
    fscanf(fptr,"%d%c",&a,&c);      //讀入字串，存成某型別變數，在txt中好用

4>  將資料寫入檔案(fprintf()/fwrite())
    fwrite(a,sizeof(int),n,fptr);   //從 指標a 指向的空間 取出 n筆 sizeof(int)大小的資料 寫入fptr檔案
    fprintf(fptr,"%d\n",a);         //將某型別變數 印出 成字串，用txt打開看，可以看得到

5>  關閉檔案
    fclose(fptr);
*/


struct RandArr{
    int *a;
    int size;
    char *name;
    void setArr(int n){
        srand(time(NULL));
        a = new int[n];
        size = n;
        for(int i=0;i<n;++i)
            a[i]=(int)(n*((double)rand()/(RAND_MAX+1.0))+1);
        
        // 求最大位數d
        int d = 1;
        int ntemp = n;
        while(ntemp/10 != 0){
            ntemp /= 10; ++d;
        }
        name = new char[1+d];
        sprintf(name,"%d",n);
    }
};

int main(){

    // 100, 500, 1000, 5000, 10000, 50000, 100000, 500000
    RandArr arr[8];
    int hd=100, fhd=500;
    for(int i=0;i<8;i+=2){
        arr[i].setArr(hd);
        arr[i+1].setArr(fhd);
        hd*=10; fhd*=10;
    }

    // for(int i=0;i<arr[3].size;i++){
    //     cout << arr[3].a[i] << ",";
    //     if(!(i%25)) cout << endl;
    // }
    // cout << endl;

    

    FILE *fptr;
    for(int q=0;q<8;++q){
        // Create Path
        char *path;
        path = new char[22+arr[q].size];
        sprintf(path,"/Users/jonaswu/cfile/input%s.txt",arr[q].name);
        // cout << path;

        int tempN = arr[q].size-1;
        
        fptr = fopen(path,"r+");
        if(fptr == NULL) fptr = fopen(path,"w+");

        // Write data to "file.txt"
        wirteIntArr(fptr,arr[q].a,1,tempN);
        // Read data from "file.txt"
        readIntArr(fptr,arr[q].a,1,&tempN);
        
        fclose(fptr);
        delete[] path;
        cout << q <<",";
    }
}
