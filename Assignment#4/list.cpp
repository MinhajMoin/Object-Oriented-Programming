#include <stdlib.h>
#include "include/list.h"

using namespace std;

void mylist::append(int val){

    if (start==NULL)
    {
        node* p = new node;
        if(p==NULL){cerr<<"Unable to allocate memory"<<endl; exit(0);}

        p->val = val;
        start = p;
    }
    else{
        //go to list's end
        node* s = start;
        while (s->next) s=s->next;

        node* p = new node;
        if(p==NULL){cerr<<"Unable to allocate memory"<<endl; exit(0);}

        p->val = val;
        s->next = p;
    }
}

//Shows a string representation of the list on the console
void mylist::print()
{
    node* s = start;
    cout<<"{";
    while(s)
    {
        cout<<s->val << ',';
        s=s->next;
    }
    cout<<"}";
}

//Returns a string representation of the list
string mylist::display()
{
    string str = "{";
    for (int i=0;i<length();i++)
    {
        stringstream ss("");
        ss << get_value_at(i);
        if (i!= length()-1)
        {
            ss << ',';
        }
        str+=ss.str();
    }
    str += "}";
    return str;
}


/*
We defined the insert operation to be strictly different from append
which means that insert won't be able to add to the end of the array.
Including this behaviour requires trivial change in code.
*/


void mylist::insert(int ind, int val)
{
    if(ind<0 || ind>=length())
        cerr<<"Invalid index passed  to insert()"<<endl;


    node* p = new node;
    if(p==NULL){cerr<<"Unable to allocate memory"<<endl; exit(0);}
    p->val = val;


    //By definition if we reach here, start!=NULL

    if(start->next==NULL)
    {
        node* tmp = start;
        start = p;
        start->next = tmp;
    }
    else{
        //now go to the appropriate location
        node* behind = start;
        node* ahead  = start->next;
        for (int i=1; i<ind; i++){
            behind = ahead;
            ahead  = ahead->next;
        }
        behind->next = p;
        p->next = ahead;
    }
}


 //Traverse the whole list and calculate the length of the list
 int mylist::length()
 {
    node* s = start;
    int i=0;
    while(s)
    {
        s=s->next;
        i++;
    }
    return i;
}


//remove the value saved in the list at the given index
void mylist::remove_at(int ind)
{
        if(ind<0 || ind>=length())
        {
            cerr<<"Invalid index passed to remove_at()"<<endl;
            exit(-1);
        }

    node *behind = start;
    if(ind==0)
    {
        start = start->next;
        delete behind;
    }
    else{
        //now go to the appropriate location
        node* ahead  = behind->next;
        for (int i=1; i<ind; i++){
            behind = ahead;
            ahead  = ahead->next;
        }
        behind->next = ahead->next;
        delete ahead;
    }
}

//get the index of the given object
int mylist::get_value_index(int val){

    int index = -1;
    node *tmp = start;
    while(tmp){
        index++;
        if(tmp->val==val)
            break;
        tmp = tmp->next;
    }

    if(tmp) return index;
    else    return -1;
}


//Get the value saved in the list at the given index
int& mylist::get_value_at(int index){

    if(index<0 || index>=length())
    {
        cerr<<"Invalid index passed  to get_value_at()"<<endl;
        exit(-1);
    }

    node *s = start;
    for (int i=0; i<index; i++)
        s= s->next;

    return s->val;
}

//Copy Constructor
mylist::mylist(mylist& List)
{
    for (int i=0;i<List.length();i++)
    {
        this->append(List.get_value_at(i));
    }
}

//Assignment Operator Overload
void mylist::operator=(mylist& List)
{
    ClearList();
    for (int i=0;i<List.length();i++)
    {
        this->append(List.get_value_at(i));
    }
}

//Delete the whole list
void mylist::ClearList()
{
    while(length()>0)
    {
        this->remove_at(0);
    }
}

//+ operator overload when a list is added
mylist& mylist::operator+(mylist& List)
{
    mylist* ptr;
    ptr = new mylist(*this);
    for (int i=0;i<List.length();i++)
    {
        ptr->append(List.get_value_at(i));
    }
    return *ptr;
}

//+ operator overload when a number is added
mylist& mylist::operator+(int Num)
{
    mylist* ptr;
    ptr = new mylist(*this);
    ptr->append(Num);
    return *ptr;
}

//- operator overload. Remove all occurrences of the given number
mylist& mylist::operator-(int Num)
{
    mylist* ptr;
    ptr = new mylist(*this);
    for (int i=0;i<ptr->length();i++)
    {
        if (ptr->get_value_at(i)==Num)
        {
            ptr->remove_at(i);
            i=-1;
        }
    }
    return *ptr;
}

//Subscript operator overload
int& mylist::operator[](int index)
{
    if (index <0)
    {
        index = length() + index;
    }
    else if (index >= length())
    {
        index = index % length();
    }
    return get_value_at(index);
}

//== Operator overload
bool mylist::operator==(mylist& List)
{
    if(List.length() != this->length()) return false;
    for (int i=0;i<length();i++)
    {
        if (List.get_value_at(i)!=get_value_at(i))
        {
            return false;
        }
    }
    return true;
}
//Destructor
mylist::~mylist()
{
    ClearList();
}
