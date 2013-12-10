#ifndef  _CLIPDOMIN_H
#define  _CLIPDOMIN_H

#include <time.h>
#include <sstream>
#include <string>
#include <list>

using namespace std;

class ClipItem;

enum ClipType{
    CT_Mark,
    CT_Note
};

class Book{
public:
    int id;
    string name;
    int count;
    list<ClipItem*> items;

    Book():id(0), count(0), items(0){

    };
};

class ClipItem{
public:
    int id;
    ClipType type;
    time_t time;
    int posStart;
    int posEnd;
    string context;
    Book *book;

public:
    ClipItem(): id(0){
    }
};

#endif