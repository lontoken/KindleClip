#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <cstring>
#include <locale>

#include "ClipDomin.h"
#include "CreatDir.h"
#include "StrCoding.h"

using namespace std;

char* trim(char *str)
{
    char *str_last, *str_cur;
    if(str == NULL) return NULL;
    for(; *str==0x20 || *str=='\t'; ++str);
    for(str_last=str_cur=str; *str_cur!='\0'; ++str_cur)
        if(*str_cur!=0x20 && *str_cur!='\t') str_last=str_cur;

    *++str_last=0;
    return str;
}

/****************************************************************************
函数名称: str_to_hex
函数功能: 字符串转换为十六进制
输入参数: string 字符串 cbuf 十六进制 len 字符串的长度。
输出参数: 无
*****************************************************************************/ 
static int str_to_hex(char *string, char *cbuf, int len)
{
 	unsigned char high, low;
	int idx, ii=0;
	for (idx=0; idx<len; ++idx) 
	{
		high = (string[idx] & 0xF0) >> 4;
		low = string[idx] & 0x0F;
		
		if(high >= 0x0 && high <= 0x09)
			high = high + '0';
		else if(high >= 0x0a && high <= 0x0f)
			high = high + 'A' - 10;
		else
			return -1;

        if(low >= 0x0 && low <= 0x09)
			low = low + '0';
		else if(low >= 0x0a && low <= 0x0f)
			low = low + 'A' - 10;
		else
			return -1;
		
        cbuf[ii++] = high;
		cbuf[ii++] = low;
	}
	return 0;
}

/****************************************************************************
函数名称: hex_to_str
函数功能: 十六进制转字符串
输入参数: ptr 字符串 buf 十六进制 len 十六进制字符串的长度。
输出参数: 无
*****************************************************************************/ 
static void hex_to_str(char *ptr,unsigned char *buf,int len)
{
	for(int i = 0; i < len; i++)
	{
		sprintf(ptr, "%02x",buf[i]);
		ptr += 2;
	}
}


int main(int argv, char* argc){
    cout << "start" << endl; 

    char t;
    cin >> t;

    int line = 0;   
    const int LINE_LENGTH = 50000; 
    char strBuf[LINE_LENGTH];

    ifstream fin;
    fin.open("My Clippings.txt");

    if (!fin.is_open()){
        cout << "Error opening file" << endl; 
        exit (1);
    }

    string title;
    string preTitle;
    string des;
    string context;
    int iCount = 0;
    int idxBook = 0;
    int idxItem = 0;

    list<Book*> books;
    Book *preBook = NULL;
    Book *curBook = NULL;
    ClipItem *curItem = NULL;


    while(!fin.eof()){
        ++iCount;

        if(iCount >= 4524){
            cout << "debug" << endl;
        }

        fin.getline(strBuf, LINE_LENGTH);
        
        char *str = strBuf;
        str = trim(str);

        switch(iCount%5){
            case 1:
                {
                    title.assign(str);

                    int i = title.find("﻿我的剪贴");

                    if(i >= 0){
                        ++iCount;
                        fin.getline(strBuf, LINE_LENGTH); 
                        ++iCount;
                        fin.getline(strBuf, LINE_LENGTH);
                        ++iCount;
                        fin.getline(strBuf, LINE_LENGTH);
                        ++iCount;
                        fin.getline(strBuf, LINE_LENGTH);
                        continue;
                    }

                    if(preTitle == title){
                        (*curBook).count++;
                    }else{
                        preBook = curBook;
                        curBook = new Book();
                        (*curBook).id = ++idxBook;
                        (*curBook).name.assign(title);
                        preTitle.assign(title);
                        books.push_back(curBook);
                        idxItem = 0;
                    }

                    break;
                }
            case 2:
                {
                    //- 我的标注 位置74-83 | 已添加至 2013年6月9日 星期日 21:11:37
                    des.assign(str);

                    curItem = new ClipItem();
                    (*curItem).book = curBook;
                    (*curItem).id = ++idxItem;

                    if(des.find_first_of("- 我的标记") == 0){
                        (*curItem).type = CT_Mark;
                    }else if(des.find_first_of("- 我的笔记") == 0){
                        (*curItem).type = CT_Note;
                    }

                    (*curBook).items.push_back(curItem);          

                    //int pos = des.find_first_of("位置");
                    //int sep = des.find_first_of("|");
                    //int sepNum = des.find_first_of("-", 0, 2);
                    //string start = des.substr(pos + 4, sepNum - pos - 4);
                    //string end = des.substr(sepNum + 1, sep - sepNum - 2);
                    //(*curItem).posStart = atoi(start.c_str());
                    //(*curItem).posEnd = atoi(end.c_str());

                    break;
                }
            case 3:
                //title.assign(str);
                break;
            case 4:
                {
                    context.assign(str);

                    if(context.empty()){
                        ++iCount;
                        fin.getline(strBuf, LINE_LENGTH);
                        continue;
                    }

                    (*curItem).context.assign(context);

                    //cout << (*curItem).context << endl;

                    break;
                }
            case 5:
                //title.assign(str);
                break;
            default:
                break;
        }
    }
    fin.close();

    
    CreatDir("./evernote");
    fstream fout;

    strCoding cfm;
    string oriName;
    string fileName;
    char idxStr[2] = {0};
    int idx = 0;

    char hexBuf[1000] = {0};

    for(list<Book*>::iterator it = books.begin(); it != books.end(); ++it){
        Book *curBook = *it;

        idx++;

        cfm.UTF_8ToGB2312(oriName, (char *)curBook->name.data(), strlen(curBook->name.data()));
        //cout<<"tmep: " << Temp<<endl;


        fileName.clear();
        fileName.append("./evernote/");
        fileName.append(oriName);
        fileName.append(".md");

        fout.open(fileName.c_str(), ios_base::out);
        if (!fout.is_open()){
            cout << "Error opening file: " << endl; 
            continue;
        }

        fout << (*curBook).name << endl;
        fout << "====" << endl;
        
        for(list<ClipItem*>::iterator itItem = (*curBook).items.begin(); itItem != (*curBook).items.end(); ++itItem){
            ClipItem *tmpItem = *itItem;
            fout << (*tmpItem).id << ".    " << (*tmpItem).context << " " << endl;
        }

        fout.close();
    }    
    

    /*
    fstream fout;

    fout.open("evernote.md", ios_base::out);
    if (!fout.is_open()){
        cout << "Error opening file: " << endl; 
        exit;
    }

    for(list<Book*>::iterator it = books.begin(); it != books.end(); ++it){
        Book *curBook = *it;

        fout << "##" << (*curBook).name << "##" << endl;
        
        for(list<ClipItem*>::iterator itItem = (*curBook).items.begin(); itItem != (*curBook).items.end(); ++itItem){
            ClipItem *tmpItem = *itItem;
            fout << (*tmpItem).id << ".    " << (*tmpItem).context << " " << endl;
        }

        fout << "" << endl;
        fout << "" << endl;
        fout << "" << endl;
        fout << "" << endl;
    } 
    
    fout.close();
    */

    return 0;
}