#include "StrCoding.h"

using namespace std;


int __main()
{ 
    
     strCoding cfm;
     string keyword="大家好,欢迎你";
     string Temp="";
     string Output="";

     //把关键字做url的utf8编码
     Temp= cfm.UrlUTF8((char *)keyword.data());
     cout<<Temp<<endl;
    
     //把url的utf8编码的结果解码
     Temp =cfm.UrlUTF8Decode(Temp);
     cout<<Temp<<endl;

     //把关键字做url的gb2312编码
     Temp =cfm.UrlGB2312((char *)keyword.data());
     cout<<Temp<<endl;
     
     //把url的gb2312编码的结果解码
     Temp =cfm.UrlGB2312Decode(Temp);
     cout<<Temp<<endl;


     //把关键字GB2312转UTF_8
    
     cfm.GB2312ToUTF_8(Output,(char *)keyword.data(),strlen(keyword.data()));
     cout<<Output<<endl;

     //把GB2312转UTF_8转为中文
     cfm.UTF_8ToGB2312(Temp,(char *)Output.data(),strlen(Output.data()));
     cout<<Temp<<endl;


    //system("pasue");
     getchar();

    return 0;
    //
}