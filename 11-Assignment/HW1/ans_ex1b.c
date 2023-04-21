#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

void initialize(int a[SIZE],int* p){
    for(int j=*p;j>=0;--j) a[j]=0;
    a[0]=1;
    *p=0;
}

void tidyUpNum(int a[SIZE],int* p){
    int i=0,p_old=*p;
    while(a[p_old] != 0){
        a[i+1]+=(a[i]/10);
        a[i]=a[i]%10;
        i++;
        if(i>=p_old) p_old=i;
    }
    *p=p_old-1;
}

void printNum(int a[SIZE],int *p){
	for(int j=*p;j>=0;--j)
		printf("%d",a[j]);
    puts("");
}

void Fact(int a[SIZE],int *p,int n){
    if(n==0) a[0]=1;
    else
        for(int i=1;i<=n;++i){
            for(int j=*p;j>=0;--j) a[j]*=i;
            tidyUpNum(a,p);
            printf("%d!=",i);
            printNum(a,p);
        }
}

int main(void){
    int a[SIZE]={0};
    int input[SIZE]={0};
    int p=0,i=0;

    do{
        scanf("%d",&input[i]);
        i++;
    }while(input[i-1]!=0);
    for(int j=0;j<i;++j){
        initialize(a,&p);
        Fact(a,&p,input[j]);
        puts("");
    }
        
    return 0;
}

