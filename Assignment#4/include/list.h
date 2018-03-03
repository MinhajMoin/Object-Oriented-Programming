#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "node.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class mylist{
public:

    mylist(){start=NULL;}
    void append(int);
    void insert(int, int);
    void print();
    int length();
    void remove_at(int);
    int get_value_index(int);
    int& get_value_at(int);
    mylist( mylist& List);
    mylist& operator+(mylist&);
    string display();
    mylist& operator+(int);
    //operator=(mylist&);
    //operator=(int&;
    bool operator==(mylist&);
    mylist& operator-(int);
    int& operator[](int);
    void operator=(mylist& List);
    ~mylist();
    void ClearList();

private:
    node* start=NULL;
};

#endif // LIST_H_INCLUDED
