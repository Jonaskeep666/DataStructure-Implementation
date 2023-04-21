#ifndef _MYFILE_HPP_
#define _MYFILE_HPP_

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

    // int aw[11]={0,1,2,3,4,5,6,7,8,9,10};
    // int size_a= 11;
    // int bw[11];
    // int size_b=0;

    // // Step 1：宣告一個指向檔案的指標
    // FILE *fptr;

    // // Step 2：先開開看檔案是否存在，若檔案不存在，則新增檔案
    // fptr = fopen("/Users/jonaswu/cfile/ouput.txt","r+");
    // if(fptr == NULL) fptr = fopen("/Users/jonaswu/cfile/ouput.txt","w+");

    // // Step 3：開始讀寫資料
    // // Write data to "file.txt"
    // rewind(fptr);
    // fprintf(fptr,"%d\n",size_a);
    // for(int i=0;i<=10;i++){
    //     fprintf(fptr,"%d\n",aw[i]);
    // }
    // // Read data from "file.txt"
    // rewind(fptr);
    // fscanf(fptr,"%d",&size_b);
    // for(int i=0;i<=10;i++){
    //     fscanf(fptr,"%d\n",&bw[i]);
    // }
    // // 驗證一下獨讀到的資料
    // cout << size_b <<":";
    // for(int i=0;i<=10;i++)
    //     cout << bw[i] <<",";
    // cout << endl;

    // // Step 4：關閉檔案
    // fclose(fptr);

#endif
