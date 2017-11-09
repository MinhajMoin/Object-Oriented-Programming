#ifndef NODE_H
#define NODE_H
#include "Entity.h"
struct Node
{

    Node()
    {
        ent=NULL;
        next=NULL;
        prev=NULL;
    }
    ~Node()
    {
        delete ent;
    }
    Entity* ent;
    Node* next;
    Node* prev;
    //bool operator==()
};

#endif // NODE_H
