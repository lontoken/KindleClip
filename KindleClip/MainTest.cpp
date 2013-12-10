#include "StrCoding.h"

using namespace std;


int __main()
{ 
    
     strCoding cfm;
     string keyword="��Һ�,��ӭ��";
     string Temp="";
     string Output="";

     //�ѹؼ�����url��utf8����
     Temp= cfm.UrlUTF8((char *)keyword.data());
     cout<<Temp<<endl;
    
     //��url��utf8����Ľ������
     Temp =cfm.UrlUTF8Decode(Temp);
     cout<<Temp<<endl;

     //�ѹؼ�����url��gb2312����
     Temp =cfm.UrlGB2312((char *)keyword.data());
     cout<<Temp<<endl;
     
     //��url��gb2312����Ľ������
     Temp =cfm.UrlGB2312Decode(Temp);
     cout<<Temp<<endl;


     //�ѹؼ���GB2312תUTF_8
    
     cfm.GB2312ToUTF_8(Output,(char *)keyword.data(),strlen(keyword.data()));
     cout<<Output<<endl;

     //��GB2312תUTF_8תΪ����
     cfm.UTF_8ToGB2312(Temp,(char *)Output.data(),strlen(Output.data()));
     cout<<Temp<<endl;


    //system("pasue");
     getchar();

    return 0;
    //
}