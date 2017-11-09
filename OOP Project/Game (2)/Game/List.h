#ifndef LIST_H
#define LIST_H
#include "Node.h"

class List
{
public:
    List();
    ~List();
    List(const List&);
    List& operator = (const List&);//assignment operator
    int size() const; //simply returns an int representing the length of the list, does so by incrementing a local variable on discovering each node and returning the result
    bool append(Entity*);
    void clean();//deletes the first nodes whose alive has been set to 0
    bool removeNodeAtInd(int);//returns 1 if the node is found and removed, 0 otherwise
    int getNodeInd(Node*);//returns index of the given node if found in the list, -1 if not found
    Entity* getEntAtInd(int) const;//returns the entity at the given ind
    void empty();//Force empties current list, deletes all nodes and sets the list to inital condition
    void render(long int&, SDL_Renderer*);
    //friend void collisionHandler(Entity*,Entity*);
    //friend void collisionHandler(Entity*,List*);
    friend class Game;
private:
    Node* start;
    Node* end;
};

#endif // LIST_H
