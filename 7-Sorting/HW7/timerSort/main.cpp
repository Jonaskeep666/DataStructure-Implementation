#include <iostream>
#include <cstdlib>
#include <ctime>
#include "myfile.hpp"
#include "search.hpp"
#include "sorting.hpp"
using namespace std;

struct Filename{
    char *name;
    int length;
    void setNum(int n){
        length = n;
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

struct SortingMethod{
    char *name;
    int no;
    SortingMethod(int no_){
        no = no_;
        switch (no){
            case 1:
                name = new char[15];
                sprintf(name,"Selection Sort");
                break;
            case 2:
                name = new char[15];
                sprintf(name,"Insertion Sort");
                break;
            case 3:
                name = new char[15];
                sprintf(name,"Heap Sort");
                break;
            case 4:
                name = new char[15];
                sprintf(name,"Merge Sort");
                break;
            case 5:
                name = new char[15];
                sprintf(name,"Quick Sort");
                break;
            case 6:
                name = new char[15];
                sprintf(name,"Radix Sort");
                break;
            case 7:
                name = new char[15];
                sprintf(name,"qsort in C");
                break;
            case 8:
            default:
                name = new char[15];
                sprintf(name,"Sort in C++");
                break;
        }
        cout << name <<endl;
    }
    double Sort(int *a,int n,int start,int r){
        clock_t t1=0,t2=0;
        switch (no){
            case 1:
                t1 = clock();
                selectionSort(a,n);
                t2 = clock();
                break;
            case 2:
                t1 = clock();
                insertionSort(a,n);
                t2 = clock();
                break;
            case 3:
                t1 = clock();
                heapSort(a,n);
                t2 = clock();
                break;
            case 4:
                t1 = clock();
                rMergeSort(a,start,n);
                t2 = clock();
                break;
            case 5:
                t1 = clock();
                aQuickSort(a,start,n);
                t2 = clock();
                break;
            case 6:
                t1 = clock();
                radixSort(a,r,n);
                t2 = clock();
                break;
            case 7:
                t1 = clock();
                qsort(a,n+1,sizeof(int),compare);
                t2 = clock();
                break;
            case 8:
            default:
                t1 = clock();
                sort(a,a+n+1);
                t2 = clock();
                break;
        }
        return ((double)(t2-t1))/CLOCKS_PER_SEC;
    }
};

// 驗證一下獨讀到的資料
void printArr(int *a, int n){
    cout << "\n" << n <<":"<<endl;
    for(int i=1;i<=n;i++){
        cout << a[i] <<",";
        if(!((i+1)%25)) cout << endl;
    }
    cout << endl;
}

// 計算陣列的平均
double calAvg(double *t,int n){
    double sum = 0.0;
    for(int i=0;i<n;i++){
        sum += t[i];
    }
    return sum/(double)n;
}

int main(){
    // Set input filename
    Filename fileNum[8];
    int hd=100, fhd=500;
    for(int i=0;i<8;i+=2){
        fileNum[i].setNum(hd);
        fileNum[i+1].setNum(fhd);
        hd*=10; fhd*=10;
    }

    FILE *fptr, *optr;

    // 紀錄10次排序的時間，透過avg儲存平均排序時間
    double tmr[10]={0.0}, avg=0.0;
    int avgCtrl = 0;  //當 avgCtrl=1 時，表示單次排序超過5分鐘，無需計算平均值

    // Set Sorting Method (從第1種 試到 第8種)
    int md;
    for(md=0;md<8;md++){
        SortingMethod method(md+1);

        // Open output file（輸出 第1種 試到 第8種 排序法 的時間紀錄）
        char *opath;
        opath = new char[40];
        sprintf(opath,"/Users/jonaswu/cfile/time_%d.txt",(md+1));
        // cout << opath;
        optr = fopen(opath,"w+");
        fprintf(optr,"%s\n",method.name);   //先印出「排序法的名稱」

        // 嘗試 資料筆數 100、500、1000、5000 ~ 500000 (共8種)
        for(int p=0;p<3;++p){
            // 印出 正在嘗試的資料
            fprintf(optr,"%s Datas\n",fileNum[p].name);
            cout << fileNum[p].name << "Datas" << endl;
            
            avg=0.0;
            avgCtrl = 0;

            // 每種「資料筆數」嘗試「10次」
            for(int q=0; q<10 && tmr[q]<=300.0 ;++q){
                cout << q+1 <<":";
            
                // Open input file
                char *ipath;
                ipath = new char[40+fileNum[p].length];
                sprintf(ipath,"/Users/jonaswu/cfile/input%s.txt",fileNum[p].name);
                // cout << ipath;
                
                fptr = fopen(ipath,"r");
                if(fptr == NULL) cout << ipath << " doesn't exist." <<endl;
                else{
                    // 讀取 要排序的資料
                    // Arr arr;
                    int *a;
                    int n=0;

                    rewind(fptr);
                    fscanf(fptr,"%d",&n);
                    a = new int[n+1];
                    for(int i=1;i<=n;i++){
                        fscanf(fptr,"%d\n",&a[i]);
                    }

                    // 排序 並且 紀錄 每次排序的時間
                    tmr[q] = method.Sort(a,n,1,10);
                    cout << tmr[q] <<endl;
                    if(tmr[q]>=300){
                        cout << "> 5 mins" <<endl;
                        avgCtrl=1;
                    }
 
                    delete[] a;
                }
                fclose(fptr); 
                delete[] ipath;
            }
            // 每10次排序完成，計算平均排序時間，並印出
            if(!avgCtrl){
                avg = calAvg(tmr,10);
                cout << "AVG:" << avg <<endl;
                fprintf(optr,"AVG:%lf\n",avg);
            }
            else{
                cout << "AVG: > 5 mins\n" << endl;
                fprintf(optr,"AVG: > 5 mins\n");
            }
        }

        fclose(optr);
        delete[] opath;
    }
}
